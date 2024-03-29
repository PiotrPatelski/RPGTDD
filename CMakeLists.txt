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

include(CTest)

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
    "${sfml_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/Tests/*")

set(COMPONENT_PATHS
    "${PROJECT_SOURCE_DIR}/Src/Core/*"
    "${PROJECT_SOURCE_DIR}/Src/States/*"
    "${PROJECT_SOURCE_DIR}/Src/Gui/*"
    "${PROJECT_SOURCE_DIR}/Src/FileMgmt/*"
    "${PROJECT_SOURCE_DIR}/Src/VectorMath/*"
    "${PROJECT_SOURCE_DIR}/Src/Events/*"
    "${PROJECT_SOURCE_DIR}/Src/Types/*"
    "${PROJECT_SOURCE_DIR}/Src/Tiles/*")

add_subdirectory(Src)

enable_testing()

add_subdirectory(Tests)

add_custom_target(copy_config ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Config
        ${PROJECT_BINARY_DIR}/Config
        COMMENT "Copying Config into binary directory")

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Assets
        ${PROJECT_BINARY_DIR}/Assets
        COMMENT "Copying Assets into binary directory")

add_dependencies(${PROJECT_NAME} copy_config)
add_dependencies(${PROJECT_NAME} copy_assets)












