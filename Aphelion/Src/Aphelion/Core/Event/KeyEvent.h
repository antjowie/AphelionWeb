#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"
#include "Aphelion/Core/Input/KeyCodes.h"

namespace ap
{
class KeyEvent : public Event
{
  public:
    APHELION_API KeyEvent(int keyCode) : keyCode(keyCode)
    {
    }

    APHELION_API int GetKeyCode() const
    {
        return keyCode;
    }

    APHELION_API std::string ToString() const override
    {
        std::stringstream ss;

        ss << GetName() << ": key " << keyCode;
        return ss.str();
    }

    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

  protected:
    int keyCode;
};

class KeyPressedEvent : public KeyEvent
{
  public:
    APHELION_API KeyPressedEvent(int keyCode, unsigned repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount)
    {
    }

    APHELION_API unsigned GetRepeatCount() const
    {
        return repeatCount;
    }

    EVENT_CLASS_TYPE(EventType::KeyPressed)

  private:
    unsigned repeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
  public:
    APHELION_API KeyReleasedEvent(int keyCode) : KeyEvent(keyCode)
    {
    }

    EVENT_CLASS_TYPE(EventType::KeyReleased)
};

/**
 * Returns a typed key
 *
 * According to the <a
 * href="https://www.glfw.org/docs/latest/group__input.html#ga556239421c6a5a243c66fca28da9f742">
 * GLFW documentation</a> we have a character callback. Characters can be
 * more than one character so the KeyPressedEvent doesn't suffice
 */
class KeyTypedEvent : public KeyEvent
{
  public:
    APHELION_API KeyTypedEvent(int keyCode) : KeyEvent(keyCode)
    {
    }

    EVENT_CLASS_TYPE(EventType::KeyTyped)
};
} // namespace ap
