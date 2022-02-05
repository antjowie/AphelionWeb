#include "Aphelion/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.h>

namespace ap
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : dirtyFlag(true), position(0), degrees(0)
{
    SetProjection(left, right, bottom, top);
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    projectionMatrix = glm::ortho(left, right, bottom, top);
    dirtyFlag = true;
}

void OrthographicCamera::CalculateMatrices() const
{
    if (!dirtyFlag)
        return;
    viewMatrix = glm::inverse(glm::translate(glm::mat4(1), position) *
                              glm::rotate(glm::mat4(1), glm::radians(degrees), glm::vec3(0, 0, 1)));

    viewProjectionMatrix = projectionMatrix * viewMatrix;
    dirtyFlag = false;
}
} // namespace ap
