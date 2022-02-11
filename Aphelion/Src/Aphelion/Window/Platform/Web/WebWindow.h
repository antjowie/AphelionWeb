#pragma once
#include "Window.h"

class SDL_Window;

namespace ap
{
class APHELION_API WebWindow : public Window
{
public:
    WebWindow(WindowProps props);

    virtual void Update() override final;

    virtual unsigned GetWidth() const override final;
    virtual unsigned GetHeight() const override final;

    virtual void SetVSync(bool enable) override final;

    virtual void SetEventMiddleware(EventMiddlewareFn fn) override final;
    virtual void* GetNativeWindow() override final;

private:
    SDL_Window* window;
    WindowProps props;
    EventMiddlewareFn eventMiddleware;
};
} // namespace ap
