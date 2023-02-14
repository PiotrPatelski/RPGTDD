set(MODULE_NAME Events)

set(SOURCES
    Source/StateActions.cpp
    Source/InputListener.cpp
    )

set(HEADERS
    Headers/ButtonEventHandler.hpp
    Headers/StateActions.hpp
    Headers/InputListener.hpp
    Headers/GuiActions.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC
    Core
    ${SFML_LIBS})

set(EVENTS_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM EVENTS_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/Events/*")
setup_target_for_coverage_gcovr_html(
    NAME EventsTestsCoverageHtml
    EXECUTABLE EventsTests
    DEPENDENCIES EventsTests Events
    EXCLUDE "${EVENTS_EXCLUDES}"
)