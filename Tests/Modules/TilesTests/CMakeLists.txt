set(MODULE_NAME TilesTests)

set(SOURCES
    GameMapManagerTests.cpp
    TileFieldTests.cpp
    TileMapTests.cpp
    TilePositionGeneratorTests.cpp
    TileTests.cpp)

add_executable(
    ${MODULE_NAME}
    ${SOURCES}
)

target_include_directories(${MODULE_NAME} PUBLIC ../Mocks)

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    Mocks
    Types
    Tiles
    mainUT
    gtest
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})

add_test(NAME TilesTestsInstance
         COMMAND ${MODULE_NAME})

ADD_DEFINITIONS(-D_PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")