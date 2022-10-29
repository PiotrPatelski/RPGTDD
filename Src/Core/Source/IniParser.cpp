#include <IniParser.h>

namespace Core
{

GraphicsData IniParser::fetchDataFromGraphicsFile()
{
    std::string filePath("Config/graphics.ini");
    std::ifstream targetFile(filePath);

    if(not targetFile.is_open())
    {
       throw std::runtime_error(
            std::string("ERROR::cannot open graphics INI file from given path: " + filePath));
    }

    GraphicsData result;

    targetFile >> result.width >> result.height;
    targetFile >> result.fullscreen;
    targetFile >> result.frameRateLimit;
    targetFile >> result.verticalSync;
    targetFile >> result.antialiasingLevel;
    targetFile.close();

    return result;
}

}