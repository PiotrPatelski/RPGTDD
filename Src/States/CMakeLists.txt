set(MODULE_NAME States)

set(SOURCES
    Source/State.cpp
    Source/MainMenuState.cpp
    Source/GameState.cpp
    Source/EditorState.cpp
    Source/SettingsState.cpp
    )

set(HEADERS
    Headers/State.hpp
    Headers/MainMenuState.hpp
    Headers/GameState.hpp
    Headers/EditorState.hpp
    Headers/SettingsState.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC
    Core
    Gui
    Events
    ${SFML_LIBS})

set(STATES_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM STATES_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/States/*")
setup_target_for_coverage_gcovr_html(
    NAME StatesTestsCoverageHtml
    EXECUTABLE StatesTests
    DEPENDENCIES StatesTests States
    EXCLUDE "${STATES_EXCLUDES}"
)