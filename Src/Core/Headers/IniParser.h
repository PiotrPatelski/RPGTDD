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
    const std::string buildPath;
};

}