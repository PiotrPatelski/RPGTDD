set(MODULE_NAME VectorMath)

set(SOURCES
    Source/ScreenPercentagePoint.cpp
    Source/PixelsPoint.cpp
    Source/SettingsListCalculator.cpp
    Source/ButtonTextCalculations.cpp
    Source/PauseMenuCalculator.cpp
    )

set(HEADERS
    Headers/ScreenPercentagePoint.hpp
    Headers/PixelsPoint.hpp
    Headers/SettingsListCalculator.hpp
    Headers/ButtonTextCalculations.hpp
    Headers/PauseMenuCalculator.hpp
    )

add_library(${MODULE_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${MODULE_NAME} PUBLIC "${PchPath}/stdafx.h")

target_include_directories(${MODULE_NAME} PUBLIC Headers Source)

target_link_libraries(${MODULE_NAME}
PUBLIC
    Types
    ${SFML_LIBS})

set(STATES_EXCLUDES
    "${COMPONENT_PATHS}")
list(REMOVE_ITEM STATES_EXCLUDES
    "${PROJECT_SOURCE_DIR}/Src/VectorMath/*")
setup_target_for_coverage_gcovr_html(
    NAME VectorMathTestsCoverageHtml
    EXECUTABLE VectorMathTests
    DEPENDENCIES VectorMathTests VectorMath
    EXCLUDE "${STATES_EXCLUDES}"
)