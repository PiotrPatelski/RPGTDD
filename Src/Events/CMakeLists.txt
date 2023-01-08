set(MODULE_NAME Events)

set(SOURCES
    Source/InputHandler.cpp
    Source/ButtonActions.cpp
    )

set(HEADERS
    Headers/InputHandler.hpp
    Headers/ButtonEventHandler.hpp
    Headers/ButtonActions.hpp
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