set(MODULE_NAME Types)

set(SOURCES
    Source/Window.cpp
    )

set(HEADERS
    Headers/Background.hpp
    Headers/Window.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME}
PUBLIC
    VectorMath
    FileMgmt
    ${SFML_LIBS})

set(STATES_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM STATES_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/Types/*")