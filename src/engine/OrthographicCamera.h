#pragma once

#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"

class OrthographicCamera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    const glm::vec3 GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) {m_Position = position; RecalculateViewMatrix(); }

    const float GetRotation() const { return m_Rotation; }
    void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix;}
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix;}
    const glm::mat4& GetProjViewMatrix() const { return m_ProjViewMatrix;}
private:
    void RecalculateViewMatrix();

private:
    glm::vec3 m_Position;
    float m_Rotation;
    
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjViewMatrix;

};