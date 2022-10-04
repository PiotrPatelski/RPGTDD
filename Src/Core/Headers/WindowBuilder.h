#pragma once

#include <Window.h>

namespace Core
{

class IWindowBuilder
{
public:
    IWindowBuilder(){}
    virtual ~IWindowBuilder(){}

    virtual Window build() = 0;
};

class WindowBuilder : public IWindowBuilder
{
public:
    WindowBuilder(){}
    virtual ~WindowBuilder(){}

    virtual Window build() override;
};

}