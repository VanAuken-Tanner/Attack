#include "Scene.h"

void Scene::OnImGuiRender()
{
    if(ImGui::Button("<- Back"))
    {
        exit_ = true;
    }
}