set(MODULE_NAME States)

set(SOURCES
    Source/State.cpp
    Source/MainMenuState.cpp
    )

set(HEADERS
    Headers/State.h
    Headers/MainMenuState.h
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC
    Core
    ${SFML_LIBS})