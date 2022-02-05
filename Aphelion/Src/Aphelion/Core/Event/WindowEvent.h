#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"

namespace ap
{
class WindowCloseEvent : public Event
{
  public:
    EVENT_CLASS_TYPE(EventType::WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent : public Event
{
  public:
    APHELION_API WindowResizeEvent(unsigned width, unsigned height) : width(width), height(height)
    {
    }

    APHELION_API unsigned GetWidth() const
    {
        return width;
    }
    APHELION_API unsigned GetHeight() const
    {
        return height;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width << ", " << height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
    unsigned width;
    unsigned height;
};

/// Upper left screen coordinates
class WindowMoveEvent : public Event
{
  public:
    APHELION_API WindowMoveEvent(int x, int y) : x(x), y(y)
    {
    }

    APHELION_API int GetX() const
    {
        return x;
    }
    APHELION_API int GetY() const
    {
        return y;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowMoveEvent: " << x << ", " << y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::WindowMove)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
    int x;
    int y;
};

class WindowIconifyEvent : public Event
{
  public:
    APHELION_API WindowIconifyEvent(bool iconified) : iconified(iconified)
    {
    }

    APHELION_API bool IsIconified() const
    {
        return iconified;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowIconifiedEvent: " << iconified;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::WindowIconify)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
    bool iconified;
};

class WindowFocusEvent : public Event
{
  public:
    APHELION_API WindowFocusEvent(bool focused) : focused(focused)
    {
    }

    APHELION_API bool IsFocused() const
    {
        return focused;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowFocusedEvent: " << focused;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::WindowFocus)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
    bool focused;
};

} // namespace ap
