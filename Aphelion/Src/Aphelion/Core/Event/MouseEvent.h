#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"
#include "Aphelion/Core/Input/MouseCodes.h"

#include <sstream>

namespace ap
{
class MouseButtonPressedEvent : public Event
{
  public:
    APHELION_API MouseButtonPressedEvent(int button) : button(button)
    {
    }

    APHELION_API int GetButton() const
    {
        return button;
    }
    APHELION_API unsigned GetRepeatCount() const
    {
        return repeatCount;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: button " << button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

  private:
    int button;
    unsigned repeatCount;
};

class MouseButtonReleasedEvent : public Event
{
  public:
    APHELION_API MouseButtonReleasedEvent(int button) : button(button)
    {
    }

    APHELION_API int GetButton() const
    {
        return button;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: button " << button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

  private:
    int button;
};

/**
 * Holds the new position of the mouse relative to the top left corner
 */
class MouseMovedEvent : public Event
{
  public:
    APHELION_API MouseMovedEvent(float x, float y) : x(x), y(y)
    {
    }

    APHELION_API float GetX() const
    {
        return x;
    }
    APHELION_API float GetY() const
    {
        return y;
    }
    APHELION_API std::pair<float, float> GetPosition() const
    {
        return {GetX(), GetY()};
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: x " << x << " y " << y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

  private:
    float x;
    float y;
};

class MouseScrolledEvent : public Event
{
  public:
    APHELION_API MouseScrolledEvent(float xOffset, float Offset) : xOffset(xOffset), yOffset(Offset)
    {
    }

    APHELION_API float GetXOffset() const
    {
        return xOffset;
    }
    APHELION_API float GetYOffset() const
    {
        return yOffset;
    }
    APHELION_API std::pair<float, float> GetScrollOffset() const
    {
        return {GetXOffset(), GetYOffset()};
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: xOffset " << xOffset << " yOffset " << yOffset;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

  private:
    float xOffset;
    float yOffset;
};
} // namespace ap
