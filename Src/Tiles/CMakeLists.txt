set(MODULE_NAME Tiles)

set(SOURCES
    Source/GameMapManager.cpp
    Source/TilePositionGenerator.cpp
    Source/TileField.cpp
    Source/TileMap.cpp
    Source/Tile.cpp
    )

set(HEADERS
    Headers/TileMapManager.hpp
    Headers/TileBuilder.hpp
    Headers/TileField.hpp
    Headers/TileMap.hpp
    Headers/Tile.hpp
    Headers/GameMapManager.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME}
PUBLIC
    FileMgmt
    Types
    ${SFML_LIBS})

set(STATES_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM STATES_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/Tiles/*")
setup_target_for_coverage_gcovr_html(
    NAME TilesTestsCoverageHtml
    EXECUTABLE TilesTests
    DEPENDENCIES TilesTests Tiles
    EXCLUDE "${STATES_EXCLUDES}")