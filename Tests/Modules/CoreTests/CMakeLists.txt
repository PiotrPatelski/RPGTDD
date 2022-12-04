set(MODULE_NAME CoreTests)

set(SOURCES
    GameTests.cpp
    ClockTests.cpp
    EngineTests.cpp
    WindowTests.cpp
    GameLoopTests.cpp
    IniParserTests.cpp
    CoreBuilderTests.cpp
    StateMachineTests.cpp
    AssetsManagerTests.cpp)

add_executable(
    ${MODULE_NAME} 
    ${SOURCES}
)

target_include_directories(${MODULE_NAME} PUBLIC ../Mocks)

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    Mocks
    Core
    States
    mainUT
    gtest 
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})

add_test(NAME CoreTestsInstance
         COMMAND ${MODULE_NAME})

ADD_DEFINITIONS(-D_PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")
message( ${CMAKE_SOURCE_DIR}/TestConfig )