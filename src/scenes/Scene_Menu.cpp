#include "Scene_Menu.h"

Scene_Menu::Scene_Menu(Scene*& pCurrentScene)
    : m_pCurrentScenePtr(pCurrentScene)
{

}

Scene_Menu::~Scene_Menu()
{

}

void Scene_Menu::OnRender()
{
    m_Renderer.Clear();
}

void Scene_Menu::OnImGuiRender()
{
    if(m_pCurrentScenePtr == this)
    {
        ImGui::Begin("Scenes:");

        for(auto& scene : m_Scenes)
        {
            if(ImGui::Button(scene.first.c_str()))//grab the first item in our pair (name)
                m_pCurrentScenePtr = scene.second();//grab out second item in our pair (scene ref)
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if(ImGui::Button("Exit Application"))
        {
           //TODO - figure out how to tell the game to exit
        }

        ImGui::End();
    }
    
    
}

