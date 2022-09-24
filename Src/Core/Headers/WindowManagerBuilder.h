#pragma once

#include <WindowManager.h>

namespace Core
{

class IWindowManagerBuilder
{
public:
    IWindowManagerBuilder(){}
    virtual ~IWindowManagerBuilder(){}

    virtual WindowManager build() = 0;
};

class WindowManagerBuilder : public IWindowManagerBuilder
{
public:
    WindowManagerBuilder(){}
    virtual ~WindowManagerBuilder(){}

    virtual WindowManager build() override;
};

}