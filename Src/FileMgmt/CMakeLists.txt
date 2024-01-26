set(MODULE_NAME FileMgmt)

set(SOURCES
    Source/IniParser.cpp
    Source/AssetsManager.cpp
    Source/MainMenuAssetsManager.cpp
    Source/EditorAssetsManager.cpp
    Source/ConfigManager.cpp
    )

set(HEADERS
    Headers/IniParser.hpp
    Headers/AssetsManager.hpp
    Headers/MainMenuAssetsManager.hpp
    Headers/EditorAssetsManager.hpp
    Headers/GameAssetsManager.hpp
    Headers/Config.hpp
    Headers/ConfigManager.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME} 
PUBLIC
    ${SFML_LIBS})

set(FILEMGMT_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM FILEMGMT_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/FileMgmt/*")
setup_target_for_coverage_gcovr_html(
    NAME FileMgmtTestsCoverageHtml
    EXECUTABLE FileMgmtTests
    DEPENDENCIES FileMgmtTests FileMgmt
    EXCLUDE "${FILEMGMT_EXCLUDES}"
)