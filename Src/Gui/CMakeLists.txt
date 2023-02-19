set(MODULE_NAME Gui)

set(SOURCES
    Source/Button.cpp
    Source/ButtonBuilder.cpp
    Source/ButtonMenu.cpp
    Source/ButtonMenuBuilder.cpp
    Source/MainMenuGuiManager.cpp
    Source/SettingsGuiManager.cpp
    Source/EditorGuiManager.cpp
    Source/MenuGui.cpp
    Source/EditorGui.cpp
    Source/GameGui.cpp
    Source/DropDownListBuilder.cpp
    Source/DropDownList.cpp
    )

set(HEADERS
    Headers/Button.hpp
    Headers/ButtonBuilder.hpp
    Headers/ButtonMenu.hpp
    Headers/MenuGui.hpp
    Headers/EditorGui.hpp
    Headers/GameGui.hpp
    Headers/GuiManager.hpp
    Headers/MainMenuGuiManager.hpp
    Headers/SettingsGuiManager.hpp
    Headers/EditorGuiManager.hpp
    Headers/GameGuiManager.hpp
    Headers/UserInterface.hpp
    Headers/ButtonList.hpp
    Headers/ButtonListBuilder.hpp
    Headers/DropDownListBuilder.hpp
    Headers/DropDownList.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC
    Events
    VectorMath
    ${SFML_LIBS})

set(GUI_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM GUI_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/Gui/*")
setup_target_for_coverage_gcovr_html(
    NAME GuiTestsCoverageHtml
    EXECUTABLE GuiTests
    DEPENDENCIES GuiTests Gui
    EXCLUDE "${GUI_EXCLUDES}"
)