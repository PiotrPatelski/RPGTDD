set(CMAKE_CXX_STANDARD 23)

set(PchPath "${CMAKE_SOURCE_DIR}/Src/PrecompiledHeaders")

set(SFML_LIBS 
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window)

add_subdirectory(Types)
add_subdirectory(Core)
add_subdirectory(States)
add_subdirectory(Gui)
add_subdirectory(FileMgmt)
add_subdirectory(Events)
add_subdirectory(VectorMath)
add_subdirectory(Tiles)

add_executable(${PROJECT_NAME} main.cpp)

#to use #include <Example.h> instead of relative path
target_include_directories(${PROJECT_NAME} PUBLIC Core)
target_include_directories(${PROJECT_NAME} PUBLIC States)
target_include_directories(${PROJECT_NAME} PUBLIC Gui)
target_include_directories(${PROJECT_NAME} PUBLIC FileMgmt)
target_include_directories(${PROJECT_NAME} PUBLIC Events)
target_include_directories(${PROJECT_NAME} PUBLIC VectorMath)
target_include_directories(${PROJECT_NAME} PUBLIC Tiles)
target_include_directories(${PROJECT_NAME} PUBLIC Types)
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
message(${SFML_INCLUDE_DIR} " FOUND!! ${SFML_INCLUDE_DIR}")

target_precompile_headers(${PROJECT_NAME} PRIVATE PrecompiledHeaders/stdafx.h)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Types
    Core
    States
    Gui
    FileMgmt
    Events
    Tiles
    VectorMath
    ${SFML_LIBS}
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)