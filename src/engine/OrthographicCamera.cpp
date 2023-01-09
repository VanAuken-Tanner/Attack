#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    :   m_Position(0,0,0), m_Rotation(0.0f)
    // ,
    //     m_ProjectionMatrix(glm::ortho(left, right, top, bottom, -1.0f, 1.0f)), // 16:9 - I guess.. idk how this should be sest up...
    //     m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); // 16:9 - I guess.. idk how this should be sest up...
    m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    //remember opengl goes proj view model
    m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
        glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0,0,1));

    m_ViewMatrix = glm::inverse(transform);
    m_ProjViewMatrix =  m_ProjectionMatrix * m_ViewMatrix;//again project then view

}