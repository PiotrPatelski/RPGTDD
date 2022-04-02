set(MODULE_NAME CoreTests)

set(SOURCES GameTests.cpp)

add_executable(
    ${MODULE_NAME} 
    ${SOURCES}
) 

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    Core
    mainUT
    gtest 
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})