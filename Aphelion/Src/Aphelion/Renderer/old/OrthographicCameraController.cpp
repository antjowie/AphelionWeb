#include "Aphelion/Renderer/OrthographicCameraController.h"

#include "Aphelion/Core/Application.h"
#include "Aphelion/Core/Event/ApplicationEvent.h"
#include "Aphelion/Core/Event/MouseEvent.h"
#include "Aphelion/Core/Input/Input.h"

//#include <GLFW/glfw3.h>

namespace ap
{
OrthographicCameraController::OrthographicCameraController(float aspectRatio, float degrees)
    : aspectRatio(aspectRatio), zoom(1), camera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom)
{
}

void OrthographicCameraController::OnUpdate(Timestep ts)
{
    glm::vec2 offset(0);
    constexpr glm::vec2 right(1, 0);
    constexpr glm::vec2 up(0, 1);

    if (Input::IsKeyPressed(KeyCode::W))
        offset += up;
    if (Input::IsKeyPressed(KeyCode::A))
        offset += -right;
    if (Input::IsKeyPressed(KeyCode::S))
        offset += -up;
    if (Input::IsKeyPressed(KeyCode::D))
        offset += right;

    if (Input::IsKeyPressed(KeyCode::LeftShift))
        offset *= 10.f;

    camera.SetPosition(camera.GetPosition() + glm::vec3(offset, 0.f) * ts.Seconds());

    float degrees = 0.f;
    constexpr float degOffset = 90.f;
    if (Input::IsKeyPressed(KeyCode::Q))
        degrees += degOffset;
    if (Input::IsKeyPressed(KeyCode::E))
        degrees -= degOffset;

    camera.SetRotation(camera.GetRotation() + degrees * ts);
}

void OrthographicCameraController::OnEvent(Event &e)
{
    EventDispatcher d(e);

    if (d.Dispatch<WindowResizeEvent>([&](WindowResizeEvent &e) {
            aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
            UpdateProjection();
            return false;
        }))
        return;

    if (d.Dispatch<MouseScrolledEvent>([&](MouseScrolledEvent &e) {
            float zoom = GetZoom() - e.GetYOffset();
            SetZoom(glm::max(0.5f, zoom));
            return false;
        }))
        return;
}

void OrthographicCameraController::UpdateProjection()
{
    camera.SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
}

} // namespace ap
