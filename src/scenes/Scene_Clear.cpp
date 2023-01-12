#include "Scene_Clear.h"

#include "..\Debug.h"

Scene_Clear::Scene_Clear()
    : m_clearColor {1.0f, 1.0f, 1.0f, 1.0f}
{
    Debugger<DEBUG_LEVEL>::Log_Console("Constructing Scene Clear.");
}

Scene_Clear::~Scene_Clear()
{

}

void Scene_Clear::OnUpdate(float deltaTine)
{

}

void Scene_Clear::OnRender()
{
    GL_CALL(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Scene_Clear::OnImGuiRender()
{
    ImGui::Begin("Reset");
    Scene::OnImGuiRender();

    ImGui::ColorEdit4("clear Color", m_clearColor);
    ImGui::End();
}
