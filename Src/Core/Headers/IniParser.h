#pragma once

#include <Config.h>

namespace Core
{


class IIniParser
{
public:
    IIniParser(){}
    virtual ~IIniParser(){}

    virtual void parseFileTo(GraphicsConfig&) = 0;
    virtual void parseFileTo(KeyboardConfig&) = 0;
private:
    virtual std::ifstream findAndOpenFile(const std::string& path) = 0;
};

class IniParser : public IIniParser
{
public:
    IniParser(const std::string& buildPath)
    : buildPath{buildPath}
    {}
    virtual ~IniParser(){}

    virtual void parseFileTo(GraphicsConfig&) override;
    virtual void parseFileTo(KeyboardConfig&) override;
private:
    virtual std::ifstream findAndOpenFile(const std::string& path) override;
    const std::string buildPath;
};

}