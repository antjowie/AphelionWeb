#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"
#include "Aphelion/Core/Time.h"
#include "Aphelion/Renderer/OrthographicCamera.h"

namespace ap
{
class APHELION_API OrthographicCameraController
{
  public:
    OrthographicCameraController(float aspectRatio, float degrees = 0);

    void OnUpdate(Timestep ts);
    void OnEvent(Event &e);

    OrthographicCamera &GetCamera()
    {
        return camera;
    }
    const OrthographicCamera &GetCamera() const
    {
        return camera;
    }

    void SetZoom(float zoom)
    {
        zoom = zoom;
        UpdateProjection();
    }
    float GetZoom() const
    {
        return zoom;
    }

  private:
    void UpdateProjection();

    float aspectRatio;
    float zoom;

    OrthographicCamera camera;
};
} // namespace ap
