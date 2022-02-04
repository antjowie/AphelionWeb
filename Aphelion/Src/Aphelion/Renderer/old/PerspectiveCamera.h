#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

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
        m_fovY = fovY;
        m_dirtyFlag = true;
    }
    void SetAspectRatio(float aspectRatio)
    {
        m_aspectRatio = aspectRatio;
        m_dirtyFlag = true;
    }
    void SetNear(float zNear)
    {
        m_near = zNear;
        m_dirtyFlag = true;
    }
    void SetFar(float zFar)
    {
        m_far = zFar;
        m_dirtyFlag = true;
    }

    float GetFOV() const
    {
        return m_fovY;
    }
    float GetAspectRatio() const
    {
        return m_aspectRatio;
    }
    float GetNear() const
    {
        return m_near;
    }
    float GetFar() const
    {
        return m_far;
    }

    const glm::mat4& GetProjectionMatrix() const
    {
        CalculateMatrices();
        return m_projectionMatrix;
    }
    const glm::mat4& GetViewMatrix() const
    {
        CalculateMatrices();
        return m_viewMatrix;
    }
    const glm::mat4& GetViewProjectionMatrix() const
    {
        CalculateMatrices();
        return m_viewProjectionMatrix;
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
    mutable bool m_dirtyFlag;
    mutable glm::mat4 m_projectionMatrix;
    mutable glm::mat4 m_viewMatrix;
    mutable glm::mat4 m_viewProjectionMatrix;

    float m_fovY;
    float m_aspectRatio;
    float m_near;
    float m_far;
};
} // namespace ap
