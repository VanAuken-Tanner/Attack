#include "Scene_Test.h"

#include "..\Debug.h"

Scene_Test::Scene_Test()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Constructing Testing Scene.");
    

    Debugger<DEBUG_LEVEL>::Log_Console("Fancy console logging");
}

Scene_Test::~Scene_Test()
{

}

void Scene_Test::OnUpdate(float deltaTine)
{
    Debugger<DEBUG_LEVEL>::Log_Console("Updating...");
    
}

void Scene_Test::OnRender()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Rendering...");
    m_Renderer.Clear();
}

void Scene_Test::OnImGuiRender()
{
    Scene::OnImGuiRender();
    ImGui::Begin("Test Scene:");
    
    ImGui::End();
}
