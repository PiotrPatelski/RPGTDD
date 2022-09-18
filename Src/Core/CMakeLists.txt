set(MODULE_NAME Core)

set(SOURCES
    Source/Game.cpp
    Source/GameLoop.cpp
    Source/WindowManager.cpp
    Source/WindowManagerBuilder.cpp
    )

set(HEADERS
    Headers/Game.h
    Headers/GameLoop.h
    Headers/WindowManager.h
    Headers/WindowManagerBuilder.h
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC 
    ${SFML_LIBS})