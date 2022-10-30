#include <GraphicsConfig.h>

namespace Core
{

void GraphicsConfig::fetchSettingsFromFile(IIniParser& parser)
{
    auto graphicsData = parser.fetchDataFromGraphicsFile();
    gameTitle = graphicsData.gameTitle;
    resolution = sf::VideoMode(graphicsData.width, graphicsData.height);
    fullscreen = graphicsData.fullscreen;
    verticalSync = graphicsData.verticalSync;
    frameRateLimit = graphicsData.frameRateLimit;
    contextSettings.antialiasingLevel = graphicsData.antialiasingLevel;
}


}