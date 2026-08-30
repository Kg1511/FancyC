cmake_minimum_required(VERSION 3.15)
project(calculator_pipeline_demo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING_DEMO "Build unit tests" ON)

# ---- Library (src/ -> implementation, include/ -> public API) ----
add_library(calculator src/Calculator.cpp)
target_include_directories(calculator
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# ---- App (the actual customer-facing executable) ----
add_executable(calculator_app apps/main.cpp)
target_link_libraries(calculator_app PRIVATE calculator)

# ---- Tests ----
if(BUILD_TESTING_DEMO)
    enable_testing()
    find_package(GTest REQUIRED)
    add_executable(unit_tests tests/test_calculator.cpp)
    target_link_libraries(unit_tests PRIVATE calculator GTest::gtest GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

# ---- Install / Artifact rules ----
install(TARGETS calculator calculator_app
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# ---- Packaging (CPack -> step 11 "Packaging" in the pipeline) ----
set(CPACK_PACKAGE_NAME "calculator_pipeline_demo")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
if(WIN32)
    set(CPACK_GENERATOR "WIX;ZIP")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB;TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "you@example.com")
endif()
include(CPack)
