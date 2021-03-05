#pragma once
#include "Window.hpp"

class SDL_Window;

namespace ap {
class APHELION_API WebWindow : public Window {
 public:
  WebWindow(WindowProps props);

  virtual unsigned GetWidth() const override final;
  virtual unsigned GetHeight() const override final;

  virtual void SetEventMiddleware(EventMiddlewareFn fn) override final;
  virtual void Update() override final;
  virtual void SetVSync(bool enable) override final;

  /**
   * Return the native window
   *
   * This is required to set up the ImGui renderer
   */
  virtual void* GetNativeWindow() override final;

 private:
  SDL_Window* m_window;
  WindowProps m_props;
  EventMiddlewareFn m_eventMiddleware;
};
}  // namespace ap