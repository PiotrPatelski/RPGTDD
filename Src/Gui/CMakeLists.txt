set(MODULE_NAME Gui)

set(SOURCES
    Source/Button.cpp
    Source/ButtonBuilder.cpp
    Source/GuiManager.cpp
    )

set(HEADERS
    Headers/Button.hpp
    Headers/ButtonBuilder.hpp
    Headers/GuiManager.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC
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