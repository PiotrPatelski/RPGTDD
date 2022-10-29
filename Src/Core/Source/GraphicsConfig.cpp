#include <GraphicsConfig.h>

namespace Core
{

void GraphicsConfig::fetchSettingsFromFile(IIniParser& parser)
{
    auto graphicsData = parser.fetchDataFromGraphicsFile();
    resolution.width = graphicsData.width;
    resolution.height = graphicsData.height;
    fullscreen = graphicsData.fullscreen;
    verticalSync = graphicsData.verticalSync;
    frameRateLimit = graphicsData.frameRateLimit;
    contextSettings.antialiasingLevel = graphicsData.antialiasingLevel;
}


}