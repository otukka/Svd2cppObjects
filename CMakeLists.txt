cmake_minimum_required(VERSION 3.16)

set(PROJECT_STD_VERSION 14)

set(CMAKE_VERBOSE_MAKEFILE OFF)

project(Svd2cppObjects VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


option(BUILD_TESTS "Build tests" OFF)
option(BUILD_DRIVER "Build driver files" ON)

if(BUILD_DRIVER) 

    if(NOT DEFINED SVD_FILE)
        message(FATAL_ERROR "The parameter SVD_FILE is not defined. (${SVD_FILE})")
    endif()

    find_file(SVD_PATH ${SVD_FILE} HINTS ${CMAKE_CURRENT_LIST_DIR} REQUIRED)

    # This will install python to the project
    execute_process(COMMAND /bin/bash -c ${CMAKE_CURRENT_LIST_DIR}/install.sh)


    # This will run the 
    execute_process(COMMAND /bin/bash -c "${CMAKE_CURRENT_LIST_DIR}/run.sh ${SVD_PATH} ${CMAKE_CURRENT_BINARY_DIR}/generated/")

    add_library(Svd2cppObjects INTERFACE)

    target_include_directories(Svd2cppObjects INTERFACE inc/ "${CMAKE_CURRENT_BINARY_DIR}/generated/")

    add_library(Svd2cppObjects ALIAS Svd2cppObjects)

endif()


if(BUILD_TESTS)

    # Ctest / catch2 
    add_subdirectory(Catch2)
    add_executable(tests)

    set_property(TARGET tests  PROPERTY CXX_STANDARD ${PROJECT_STD_VERSION})
    # target_compile_options(tests PRIVATE -Wall -Wextra -pedantic -Werror -Wconversion)

    target_sources(tests PRIVATE
    tests/BitfieldTests.cpp
    tests/main.cpp
    tests/PeripheralFactoryTests.cpp
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

endif()
