#pragma once
#include <glm/gtc/quaternion.h>
#include <glm/mat4x4.h>
#include <glm/vec3.h>

#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Transform.h"

namespace ap
{
class APHELION_API PerspectiveCamera
{
  public:
    PerspectiveCamera(float fovY, float aspectRatio, float zNear, float zFar);

    void SetProjection(float fovY, float aspectRatio, float zNear, float zFar);

    void SetFOV(float fovY)
    {
        fovY = fovY;
        dirtyFlag = true;
    }
    void SetAspectRatio(float aspectRatio)
    {
        aspectRatio = aspectRatio;
        dirtyFlag = true;
    }
    void SetNear(float zNear)
    {
        near = zNear;
        dirtyFlag = true;
    }
    void SetFar(float zFar)
    {
        far = zFar;
        dirtyFlag = true;
    }

    float GetFOV() const
    {
        return fovY;
    }
    float GetAspectRatio() const
    {
        return aspectRatio;
    }
    float GetNear() const
    {
        return near;
    }
    float GetFar() const
    {
        return far;
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
    /**
     * The camera views along the -z direction. The forward points towards the +z
     * direction The transform forward and camera view direction are not the same
     */
    const glm::vec3 GetViewDirection() const
    {
        return -transform.GetForward();
    }

  public:
    Transform transform;

  private:
    void CalculateMatrices() const;

    // We calculate the matrices only upon request and cache it
    mutable bool dirtyFlag;
    mutable glm::mat4 projectionMatrix;
    mutable glm::mat4 viewMatrix;
    mutable glm::mat4 viewProjectionMatrix;

    float fovY;
    float aspectRatio;
    float near;
    float far;
};
} // namespace ap
