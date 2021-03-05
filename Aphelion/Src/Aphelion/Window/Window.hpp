#pragma once
#include <functional>
#include <string>

#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Core/Event/Event.hpp"

namespace ap {
/**
 * This function is the function that the Window forwards the events to.
 */
using EventCallbackFn = std::function<void(Event&&)>;
// Return true if handled
using EventMiddlewareFn = std::function<bool(void*)>;

/**
 * The WindowProps struct contains all the data consistent among all window
 * classes
 */
struct APHELION_API WindowProps {
 public:
  std::string title;
  unsigned width;
  unsigned height;
  EventCallbackFn eventCallback;

  WindowProps(const std::string& title = "Aphelion Engine",
              unsigned width = 1280, unsigned height = 720)
      : title(title), width(width), height(height) {}
};

/**
 * The window interface. Implementations of this interface are platform specific
 * and thus defined under the Platform folder
 */
class APHELION_API Window {
 public:
  /**
   * We override the static create function so that we won't have to bother with
   * checking the platform in other code
   */
  static std::unique_ptr<Window> Create(WindowProps props = WindowProps());

  virtual ~Window() = default;

  virtual unsigned GetWidth() const = 0;
  virtual unsigned GetHeight() const = 0;

  /**
   * Before events get handled by the window, we may want to pass them to other
   * systems first. For example, our ImGUI library wants to handle the events
   * before they are propogated to our main systems. By setting the
   * EventMiddleware, we allow our ImGUI system to handle the events first
   */
  virtual void SetEventMiddleware(EventMiddlewareFn fn) = 0;

  /**
   * Poll events, swap buffers. Whatever a window needs to do on frame
   */
  virtual void Update() = 0;
  /**
   * Application owns a window. The window needs to send events to the
   * application. To do this, Applications gives the Window an event callback
   * function.
   */
  // virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

  virtual void SetVSync(bool enable) = 0;

  /**
   * Return the native window
   *
   * This is required to set up the ImGui renderer
   */
  virtual void* GetNativeWindow() = 0;
};
}  // namespace ap