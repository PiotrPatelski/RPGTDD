set(MODULE_NAME Core)

set(SOURCES
    Source/Game.cpp
    Source/GameLoop.cpp
    Source/Window.cpp
    Source/Clock.cpp
    Source/StateMachine.cpp
    Source/Engine.cpp
    Source/IniParser.cpp
    )

set(HEADERS
    Headers/Game.h
    Headers/GameLoop.h
    Headers/Window.h
    Headers/Clock.h
    Headers/StateMachine.h
    Headers/Engine.h
    Headers/Config.h
    Headers/IniParser.h
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC 
    States
    ${SFML_LIBS})