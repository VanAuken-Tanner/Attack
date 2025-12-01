#pragma once
#include "Scene.h"

class Scene_Menu : public Scene
{
public:
    Scene_Menu(Scene*& pCurrentScenePtr);
    ~Scene_Menu();

    inline bool CloseGame() { return close_game_;}

    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;
    void OnRender() override;
    void OnHandleInput() override;

    template<typename T>
    void RegisterTest(const std::string& name)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Registering Scene - " + name);
        m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));//make pairs of scenes with an anonymous function
    }

private: 
    void SetKeyActions();
    
    Scene*& m_pCurrentScenePtr;//pointer to our current Scene(reference);
    std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes;//Vector of Scenes (paired by name and ref)
};