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
