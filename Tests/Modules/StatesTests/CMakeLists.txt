set(MODULE_NAME StatesTests)

set(SOURCES StatesTests.cpp)
set(HEADERS DummyMock.h)

add_executable(
    ${MODULE_NAME} 
    ${SOURCES}
)

add_library(StatesMocks ${HEADERS})
set_target_properties(StatesMocks PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    States
    StatesMocks
    mainUT
    gtest 
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})

add_test(NAME StatesTestsInstance 
         COMMAND ${MODULE_NAME})