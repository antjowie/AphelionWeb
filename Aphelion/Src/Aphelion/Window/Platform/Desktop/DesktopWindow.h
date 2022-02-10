#pragma once
#include "Aphelion/Window/Window.h"

class GLFWwindow;

namespace ap
{
class DesktopWindow : public Window
{
public:
    DesktopWindow(const WindowProps& props);
    ~DesktopWindow();

    virtual void Update() override final;

    virtual std::pair<unsigned, unsigned> GetSize() const override final;

    virtual void SetVSync(bool enable) override final;

    virtual void SetEventMiddleware(const EventMiddlewareFn& fn) override final
    {
        eventMiddleware = fn;
    }

    virtual void* GetNativeWindow() override final
    {
        return window;
    }

private:
    WindowProps props;
    EventMiddlewareFn eventMiddleware = nullptr;
    GLFWwindow* window = nullptr;
};
} // namespace ap
