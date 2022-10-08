set(CMAKE_CXX_STANDARD 23)

set(PchPath "${CMAKE_SOURCE_DIR}/Src/PrecompiledHeaders")

set(SFML_LIBS 
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window)

add_subdirectory(Core)
add_subdirectory(States)

add_executable(${PROJECT_NAME} main.cpp)

#to use #include <Example.h> instead of relative path
target_include_directories(${PROJECT_NAME} PUBLIC Core)
target_include_directories(${PROJECT_NAME} PUBLIC States)
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
message(${SFML_INCLUDE_DIR} " FOUND!! ${SFML_INCLUDE_DIR}")

target_precompile_headers(${PROJECT_NAME} PRIVATE PrecompiledHeaders/stdafx.h)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Core
    States
    ${SFML_LIBS}
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)