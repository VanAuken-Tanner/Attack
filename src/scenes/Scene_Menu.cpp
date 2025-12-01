#include "Scene_Menu.h"

Scene_Menu::Scene_Menu(Scene*& pCurrentScene)
    : m_pCurrentScenePtr(pCurrentScene)
{
    close_game_ = false;
    SetKeyActions();
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
            exit_scene_ = true;
            close_game_ = true;
        }

        ImGui::End();
    }
}

void Scene_Menu::OnUpdate(float deltaTime)
{

}

void Scene_Menu::OnHandleInput()
{
    InputHandler::HandleKeyEvents();
}

void Scene_Menu::SetKeyActions()
{
    InputHandler::AddKeyAction<GLFW_KEY_ESCAPE>( [this](bool pressed) { 
        exit_scene_ = true;
        close_game_ = true;
    });
}