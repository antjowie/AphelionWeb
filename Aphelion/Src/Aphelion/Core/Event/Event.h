#pragma once

#include <sstream>
#include <string>

#include "Core.h"
#include "Helper.h"
/**
 * Events are used to communicate between major systems that we want to keep
 * decoupled. One example is input. Input events have to be abstracted since
 * each platform likely requires it's own window implementation, which means
 * different input events. We abstract these in events and use the Engine as
 * a mediator to propogate these events to systems
 */
namespace ap
{
enum class EventType
{
    None = 0,
    // Window events
    WindowClose,
    WindowResize,
    WindowMove,
    WindowIconify,
    WindowFocus,

    // Input events
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = Bit(0), // Program related events such as shutdown
    EventCategoryInput = Bit(1),
    EventCategoryKeyboard = Bit(2),
    EventCategoryMouse = Bit(3),
    EventCategoryMouseButton = Bit(4),
};

#define EVENT_CLASS_TYPE(type)                                                                     \
    static EventType GetStaticType()                                                               \
    {                                                                                              \
        return type;                                                                               \
    }                                                                                              \
    virtual EventType GetEventType() const override                                                \
    {                                                                                              \
        return GetStaticType();                                                                    \
    }                                                                                              \
    virtual const char* GetName() const override                                                   \
    {                                                                                              \
        return #type;                                                                              \
    }

#define EVENT_CLASS_CATEGORY(category)                                                             \
    virtual int GetCategoryFlags() const override                                                  \
    {                                                                                              \
        return EventCategory::category;                                                            \
    }

/**
 * Base event class with type identifications
 * Use the EVENT_CLASS_TYPE(type) and EVENT_CLASS_CATEGORY(category) macro to
 * implement the functions of this class in derived classes. They serve to
 * retrieve runtime information
 */
class APHELION_API Event
{
public:
    bool handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const
    {
        return GetName();
    }

    inline bool IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & category;
    }
};

/**
 * Helper function to handle an event
 * If the template type matches the evennt type, the callback will be called
 */
class APHELION_API EventDispatcher
{
public:
    EventDispatcher(Event& event)
        : m_event(event)
    { }

    /**
   * Dispatches the event if the function type corresponds with T
   * Returns true if the callback was called (meaning the event was of correct
   * type)
   */
    template <typename T, typename F>
    bool Dispatch(const F& func)
    {
        if(m_event.GetEventType() == T::GetStaticType())
        {
            m_event.handled = func(static_cast<T&>(m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}

} // namespace ap
