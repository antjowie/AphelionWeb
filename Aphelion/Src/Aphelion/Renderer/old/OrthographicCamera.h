#pragma once
#include <glm/mat4x4.h>
#include <glm/vec3.h>

#include "Aphelion/Core/Core.h"

namespace ap
{
class APHELION_API OrthographicCamera
{
  public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);

    void SetPosition(const glm::vec3 &pos)
    {
        position = pos;
        dirtyFlag = true;
    }
    const glm::vec3 GetPosition() const
    {
        return position;
    }

    void SetRotation(float degrees)
    {
        degrees = degrees;
        dirtyFlag = true;
    }
    float GetRotation()
    {
        return degrees;
    }

    const glm::mat4 &GetProjectionMatrix() const
    {
        CalculateMatrices();
        return projectionMatrix;
    }
    const glm::mat4 &GetViewMatrix() const
    {
        CalculateMatrices();
        return viewMatrix;
    }
    const glm::mat4 &GetViewProjectionMatrix() const
    {
        CalculateMatrices();
        return viewProjectionMatrix;
    }

  private:
    void CalculateMatrices() const;

    // We calculate the matrices only upon request and cache it
    mutable bool dirtyFlag;
    mutable glm::mat4 projectionMatrix;
    mutable glm::mat4 viewMatrix;
    mutable glm::mat4 viewProjectionMatrix;

    glm::vec3 position;
    float degrees;
};
} // namespace ap
