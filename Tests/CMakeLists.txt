add_subdirectory(Modules)

add_library(mainUT mainUT.cpp)

target_link_libraries(
    mainUT
    PUBLIC
    gtest 
    gtest_main 
    gmock_main
)


