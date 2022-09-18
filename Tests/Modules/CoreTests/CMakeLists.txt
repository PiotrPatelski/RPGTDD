set(MODULE_NAME CoreTests)

set(SOURCES GameTests.cpp)
set(HEADERS
    GameMock.h
    WindowManagerMock.h
    WindowManagerBuilderMock.h)

add_executable(
    ${MODULE_NAME} 
    ${SOURCES}
)

add_library(CoreMocks ${HEADERS})
set_target_properties(CoreMocks PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    Core
    CoreMocks
    mainUT
    gtest 
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})