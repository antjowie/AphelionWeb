#pragma once
#include <sstream>

#include "Core.hpp"
#include "Event/Event.hpp"
#include "Input/MouseCodes.hpp"

namespace ap
{
class APHELION_API MouseButtonPressedEvent : public Event
{
public:
    MouseButtonPressedEvent(int button)
        : m_button(button)
    { }

    inline int GetButton() const
    {
        return m_button;
    }
    inline unsigned GetRepeatCount() const
    {
        return m_repeatCount;
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: button " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

private:
    int m_button;
    unsigned m_repeatCount;
};

class APHELION_API MouseButtonReleasedEvent : public Event
{
public:
    MouseButtonReleasedEvent(int button)
        : m_button(button)
    { }

    inline int GetButton() const
    {
        return m_button;
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: button " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseButtonReleased)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

private:
    int m_button;
};

/**
 * Holds the new position of the mouse relative to the top left corner
 */
class APHELION_API MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_x(x)
        , m_y(y)
    { }

    inline float GetX() const
    {
        return m_x;
    }
    inline float GetY() const
    {
        return m_y;
    }
    inline std::pair<float, float> GetPosition() const
    {
        return {GetX(), GetY()};
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: x " << m_x << " y " << m_y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

private:
    float m_x;
    float m_y;
};

class APHELION_API MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset, float Offset)
        : m_xOffset(xOffset)
        , m_yOffset(Offset)
    { }

    inline float GetXOffset() const
    {
        return m_xOffset;
    }
    inline float GetYOffset() const
    {
        return m_yOffset;
    }
    inline std::pair<float, float> GetScrollOffset() const
    {
        return {GetXOffset(), GetYOffset()};
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: xOffset " << m_xOffset << " yOffset " << m_yOffset;
        return ss.str();
    }

    EVENT_CLASS_TYPE(EventType::MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

private:
    float m_xOffset;
    float m_yOffset;
};
} // namespace ap
