cmake_minimum_required(VERSION 3.16)

set(PROJECT_STD_VERSION 14)

set(CMAKE_VERBOSE_MAKEFILE OFF)

project(Svd2cppObjects VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ctest / catch2 
add_subdirectory(Catch2)
add_executable(tests)

set_property(TARGET tests  PROPERTY CXX_STANDARD ${PROJECT_STD_VERSION})
# target_compile_options(tests PRIVATE -Wall -Wextra -pedantic -Werror -Wconversion)

target_sources(tests PRIVATE
tests/BitfieldTests.cpp
tests/main.cpp
tests/PeripheralTests.cpp
tests/PropertyTests.cpp
tests/RegisterTests.cpp
)

target_include_directories(tests PRIVATE inc)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Catch2/contrib/")

target_compile_definitions(tests PRIVATE TEST_HELPERS=1)

include(CTest)
include(Catch)
catch_discover_tests(tests)