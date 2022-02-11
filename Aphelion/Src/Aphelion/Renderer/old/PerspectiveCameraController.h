#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"
#include "Aphelion/Core/Time.h"
#include "Aphelion/Renderer/PerspectiveCamera.h"

namespace ap
{
class APHELION_API PerspectiveCameraController
{
  public:
    PerspectiveCameraController(float fovYRadians, float aspectRatio, float zNear = 0.1f, float zFar = 1000.f);
    ~PerspectiveCameraController()
    {
        Enable(false);
    }

    void OnUpdate(Timestep ts);
    void OnEvent(Event &e);

    // Whether to enable camera moving
    void Enable(bool enable);

    PerspectiveCamera &GetCamera()
    {
        return camera;
    }
    const PerspectiveCamera &GetCamera() const
    {
        return camera;
    }

  private:
    PerspectiveCamera camera;

    bool isRotating;
    glm::dvec2 oldCursorPos;
};
} // namespace ap
