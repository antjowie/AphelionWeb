#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Input/KeyCodes.h"
#include "Aphelion/Core/Input/MouseCodes.h"

#include <memory>

namespace ap
{
/**
 * TODO: Cursor functions take a vec2 instead of a uvec2. This should be
 * refactored
 */
class Input
{
public:
    /**
     * When cursor is disabled, the cursor will be invisible and stay centered.
     * CursorMoveEvents will still contain the new cursor position
     *
     * TODO: This maybe should be a window specific function
     */
    APHELION_API static void EnableCursor(bool enable)
    {
        return instance->EnableCursorImpl(enable);
    };

    APHELION_API static bool IsKeyPressed(KeyCode code)
    {
        return instance->IsKeyPressedImpl(code);
    }
    APHELION_API static bool IsButtonPressed(ButtonCode code)
    {
        return instance->IsButtonPressedImpl(code);
    }

    APHELION_API static void SetCursorPos(const glm::vec2& pos)
    {
        return instance->SetCursorPosImpl(pos);
    }
    APHELION_API static void SetCursorX(float x)
    {
        return instance->SetCursorXImpl(x);
    }
    APHELION_API static void SetCursorY(float y)
    {
        return instance->SetCursorYImpl(y);
    }

    /**
     * Returns the position in screen coordinates
     */
    APHELION_API static glm::dvec2 GetCursorPos()
    {
        return instance->GetCursorPosImpl();
    }
    APHELION_API static float GetCursorX()
    {
        return instance->GetCursorXImpl();
    }
    APHELION_API static float GetCursorY()
    {
        return instance->GetCursorYImpl();
    }

private:
    virtual void EnableCursorImpl(bool enable) = 0;

    virtual bool IsKeyPressedImpl(KeyCode code) = 0;
    virtual bool IsButtonPressedImpl(ButtonCode code) = 0;

    virtual void SetCursorPosImpl(const glm::vec2& pos) = 0;
    virtual void SetCursorXImpl(float x) = 0;
    virtual void SetCursorYImpl(float y) = 0;

    virtual glm::dvec2 GetCursorPosImpl() = 0;
    virtual float GetCursorXImpl() = 0;
    virtual float GetCursorYImpl() = 0;

    static std::unique_ptr<Input> Create();

    static std::unique_ptr<Input> instance;
};
} // namespace ap
