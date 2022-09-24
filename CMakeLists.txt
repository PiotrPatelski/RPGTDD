cmake_minimum_required(VERSION 3.16)

#find_package (Python COMPONENTS Interpreter Development)

include(FetchContent)

project(RPGTDD LANGUAGES CXX)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest"
    GIT_TAG "release-1.11.0")
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

set(SFML_VERSION "2.5.1")
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)
FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

#GCOVR
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)
append_coverage_compiler_flags()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

set(GCOVR_PATH "/usr/bin/gcovr")
set(COVERAGE_EXCLUDES 
    "${googletest_SOURCE_DIR}"
    "${googletest_BUILD_DIR}"
    "${sfml_SOURCE_DIR}"
    "${sfml_BINARY_DIR}")


setup_target_for_coverage_gcovr_html(
    NAME TestCoverageHtml
    EXECUTABLE CoreTests
    DEPENDENCIES CoreTests Core
)

add_subdirectory(Src)

enable_testing()

add_subdirectory(Tests)














