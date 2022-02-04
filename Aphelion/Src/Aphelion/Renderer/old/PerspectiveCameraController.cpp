#include "Aphelion/Renderer/PerspectiveCameraController.h"

#include "Aphelion/Core/Application.h"
#include "Aphelion/Core/Event/MouseEvent.h"
#include "Aphelion/Core/Input/Input.h"
#include "Aphelion/Core/Input/KeyCodes.h"

namespace ap
{
PerspectiveCameraController::PerspectiveCameraController(float fovYRadians, float aspectRatio, float zNear, float zFar)
    : m_camera(fovYRadians, aspectRatio, zNear, zFar), m_isRotating(false), m_oldCursorPos(0)
{
}

void PerspectiveCameraController::OnUpdate(Timestep ts)
{
    if (!m_isRotating)
        return;

    glm::vec3 offset(0);
    // NOTE: I flipped the forward for the camera. This is because OpenGL by
    // default 'looks' into the -z direction. We want to transform relatively
    // among the camera view dir. Camera view dir and transform forward are not
    // the same
    const glm::vec3 forward(-m_camera.transform.GetForward());
    const glm::vec3 right(m_camera.transform.GetRight());
    const glm::vec3 up(m_camera.transform.GetWorldUp());

    if (Input::IsKeyPressed(KeyCode::W))
        offset += forward;
    if (Input::IsKeyPressed(KeyCode::A))
        offset += -right;
    if (Input::IsKeyPressed(KeyCode::S))
        offset += -forward;
    if (Input::IsKeyPressed(KeyCode::D))
        offset += right;
    if (Input::IsKeyPressed(KeyCode::E))
        offset += up;
    if (Input::IsKeyPressed(KeyCode::Q))
        offset += -up;

    if (Input::IsKeyPressed(KeyCode::LeftShift))
        offset *= 10.f;

    m_camera.transform.SetPosition(m_camera.transform.GetPosition() + offset * ts.Seconds() * 5.f);
}

void PerspectiveCameraController::OnEvent(Event &e)
{
    EventDispatcher d(e);

    static bool initial = true;
    if (m_isRotating)
    {
        // For some reason camera tends to jump on first frame when capturing, so we
        // ignore first frame
        d.Dispatch<MouseMovedEvent>([&](MouseMovedEvent &e) {
            // TODO: Add a sensitivity variable for offset
            auto offset = glm::dvec2(e.GetX(), e.GetY()) - m_oldCursorPos;
            offset = offset / 25. * glm::two_pi<double>();

            if (initial)
            {
                offset = glm::dvec2(0);
                // AP_CORE_ERROR("{:.2f}{:.2f}", offset.x, offset.y);
            }

            // rhs coordinates
            // positive x is ccw rotation
            // offset is from top left
            // Move cursor right with 10 px == -x rotation
            // Cursor right is + offset, so negate x

            // Move cursor up with 10 px == +y rotation
            // Cursor up is - offset, so negate y
            m_camera.transform.Rotate(Radians(glm::vec3(-offset.y, -offset.x, 0)));
            initial = false;
            return false;
        });
    }
    else
    {
        initial = true;
    }
    // d.Dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent& e)
    //    {
    //        if (e.GetButton() == ButtonCode::Right)
    //        {
    //            Input::EnableCursor(false);
    //            m_isRotating = true;
    //        }
    //        return false;
    //    });
    // d.Dispatch<MouseButtonReleasedEvent>([&](MouseButtonReleasedEvent& e)
    //    {
    //        if (e.GetButton() == ButtonCode::Right)
    //        {
    //            Input::EnableCursor(true);
    //            m_isRotating = false;
    //        }
    //        return false;
    //    });

    m_oldCursorPos = Input::GetCursorPos();
}

void PerspectiveCameraController::Enable(bool enable)
{
    if (enable)
    {
        Input::EnableCursor(false);
        m_oldCursorPos = Input::GetCursorPos();
        m_isRotating = true;
    }
    else
    {
        Input::EnableCursor(true);
        m_isRotating = false;
    }
}
} // namespace ap
