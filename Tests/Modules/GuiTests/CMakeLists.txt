set(MODULE_NAME GuiTests)

set(SOURCES
    ButtonTests.cpp
    ButtonBuilderTests.cpp
    ButtonMenuTests.cpp
    ButtonMenuBuilderTests.cpp
    MenuGuiTests.cpp
    EditorGuiTests.cpp
    GameGuiTests.cpp
    MainMenuGuiManagerTests.cpp
    SettingsGuiManagerTests.cpp
    EditorGuiManagerTests.cpp
    GameGuiManagerTests.cpp
    DropDownListTests.cpp
    DropDownListBuilderTests.cpp)

add_executable(
    ${MODULE_NAME} 
    ${SOURCES}
)

target_include_directories(${MODULE_NAME} PUBLIC ../Mocks)

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
    Gui
    Types
    Mocks
    mainUT
    gtest 
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})

add_test(NAME GuiTestsInstance
         COMMAND ${MODULE_NAME})

ADD_DEFINITIONS(-D_PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")