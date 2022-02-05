#include "Aphelion/Renderer/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.h>

namespace ap
{
PerspectiveCamera::PerspectiveCamera(float fovY, float aspectRatio, float zNear, float zFar)
    : dirtyFlag(true), fovY(fovY), aspectRatio(aspectRatio), near(zNear), far(zFar)
{
    AP_CORE_ASSERT(fovY != 0, "FOV can't be zero");
    AP_CORE_ASSERT(aspectRatio != 0, "Aspect ratio can't be zero");
    SetProjection(fovY, aspectRatio, zNear, zFar);
}

void PerspectiveCamera::SetProjection(float fovY, float aspectRatio, float zNear, float zFar)
{
    fovY = fovY;
    aspectRatio = aspectRatio;
    near = zNear;
    far = zFar;

    dirtyFlag = true;
}

void PerspectiveCamera::CalculateMatrices() const
{
    static Transform oldT = transform;

    if (!dirtyFlag && transform == oldT)
        return;

    projectionMatrix = glm::perspective(fovY, aspectRatio, near, far);

    viewMatrix = glm::inverse(transform.GetWorldMatrix());

    viewProjectionMatrix = projectionMatrix * viewMatrix;
    dirtyFlag = false;
    oldT = transform;
}
} // namespace ap
