#pragma once

#include <WindowManager.h>

namespace Core
{

class IWindowManagerBuilder
{
public:
    IWindowManagerBuilder(){}
    virtual ~IWindowManagerBuilder(){}

    virtual std::unique_ptr<IWindowManager> build() = 0;
};

class WindowManagerBuilder : public IWindowManagerBuilder
{
public:
    WindowManagerBuilder(){}
    virtual ~WindowManagerBuilder(){}

    virtual std::unique_ptr<IWindowManager> build() override;
};

}