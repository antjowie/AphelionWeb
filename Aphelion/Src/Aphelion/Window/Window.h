#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"

#include <functional>
#include <string>

namespace ap
{
using EventCallbackFn = std::function<void(Event&&)>;
/* Return true if handled */
using EventMiddlewareFn = std::function<bool(void*)>;

struct WindowProps
{
public:
    std::string title;
    unsigned width;
    unsigned height;
    EventCallbackFn eventCb;

    WindowProps(const std::string& title = "Aphelion Engine", unsigned width = 1280, unsigned height = 720)
        : title(title), width(width), height(height)
    {
    }
};

class Window
{
public:
    // Implemented in Platform source files
    APHELION_API static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());

    APHELION_API virtual ~Window() = default;

    /**
     * Poll events, swap buffers. Whatever a window needs to do on frame.
     */
    APHELION_API virtual void Update() = 0;

    APHELION_API virtual std::pair<unsigned, unsigned> GetSize() const = 0;
    APHELION_API virtual void SetVSync(bool enable) = 0;

    /**
     * Callback will be called with the native event before window converts
     * it to an Aphelion event. Usefull for code that expects native events (ImGui backends).
     */
    APHELION_API virtual void SetEventMiddleware(const EventMiddlewareFn& fn) = 0;

    /**
     * Return the native window
     */
    APHELION_API virtual void* GetNativeWindow() = 0;
};
} // namespace ap
