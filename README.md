# calculator_pipeline_demo

Minimal C++ project demonstrating a full dev pipeline: CMake build,
Conan dependency management, GTest unit tests, Jenkins CI, packaging,
and artifact publishing.

## Structure

```
include/    Public API (calculator/Calculator.hpp)
src/        Implementation (Calculator.cpp)
tests/      Unit tests (GTest)
CMakeLists.txt   Build + install + CPack packaging rules
conanfile.txt    Declares gtest dependency
Jenkinsfile      CI pipeline: checkout -> conan install -> cmake
                 configure -> build -> test -> static analysis ->
                 package -> publish artifacts
```

## Build (with Conan)

```bash
conan install . --output-folder=build --build=missing
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
cmake --build build
ctest --test-dir build --output-on-failure
```

## Build (system GTest, no Conan)

```bash
sudo apt install libgtest-dev cmake g++
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Package (CPack)

```bash
cd build
cpack -G TGZ    # or DEB / ZIP / WIX depending on platform
```
## Build on Windows (MinGW-w64 GCC)

If Conan autodetects MSVC even though you want to build with MinGW GCC
(common when Visual Studio Build Tools are installed alongside MinGW),
override the default profile manually.

**1. Set the default Conan profile to GCC** — edit
`C:\Users\<you>\.conan2\profiles\default` to contain:

[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.version=14
compiler.libcxx=libstdc++11
compiler.cppstd=17
os=Windows


(Adjust `compiler.version` to match your installed GCC major version —
check with `gcc --version`.)

**2. Install dependencies:**

```powershell
conan install . --output-folder=build --build=missing
```

**3. Configure** — quote the toolchain path fully, specify the
`MinGW Makefiles` generator, and explicitly pass `CMAKE_BUILD_TYPE`
(Conan's generated config requires it to match the profile's
`build_type`):

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
```

**4. Build and test:**

```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

### Troubleshooting notes

- `Error: could not load cache` on `cmake --build` → the configure step
  (step 3) never completed; re-run it and check for errors.
- `Could not find toolchain file: build/conan_toolchain` with a
  `.cmake` split off separately → the `-DCMAKE_TOOLCHAIN_FILE=` path
  didn't parse as one argument. Wrap it in quotes as shown above.
- `CMake was unable to find a build program corresponding to "Ninja"` →
  no generator was specified and CMake defaulted to Ninja, which isn't
  installed. Use `-G "MinGW Makefiles"` (requires `mingw32-make.exe`,
  which ships with most MinGW-w64 distributions) or install Ninja
  separately.
- `Please, set the CMAKE_BUILD_TYPE variable` → add
  `-DCMAKE_BUILD_TYPE=Release` (or whatever `build_type` your Conan
  profile uses) to the configure command.
- If `conan profile detect` keeps finding MSVC instead of GCC, it's
  actively searching for a Visual Studio install via `vswhere`
  regardless of PATH order — hand-editing the profile file (step 1)
  is more reliable than trying to fix PATH.