#pragma once
#include <memory>

#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Window.h"
#include "Aphelion/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace ap
{
class APHELION_API WindowsWindow : public Window
{
  public:
    WindowsWindow(WindowProps &props);
    virtual ~WindowsWindow() override final;

    virtual unsigned GetWidth() const override final
    {
        return props.width;
    }
    virtual unsigned GetHeight() const override final
    {
        return props.height;
    }

    virtual void OnUpdate() override final;
    virtual void SetVSync(bool enable) override final;

    inline virtual void SetEventCallback(const EventCallbackFn &callback) override final
    {
        props.eventCallback = callback;
    }

    inline virtual void *GetNativeWindow() override final
    {
        return window;
    }

  private:
    std::unique_ptr<GraphicsContext> context;
    GLFWwindow *window;
    WindowProps props;
};
} // namespace ap
