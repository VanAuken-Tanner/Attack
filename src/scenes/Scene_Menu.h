#pragma once
#include "Scene.h"

class Scene_Menu : public Scene
{
public:
    Scene_Menu(Scene*& pCurrentScenePtr);
    ~Scene_Menu();

    void OnImGuiRender() override;
    void OnRender() override;

    template<typename T>
    void RegisterTest(const std::string& name)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Registering Scene - " + name);
        m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));//make pairs of scenes with an anonymous function
    }

private:
    
    Scene*& m_pCurrentScenePtr;//pointer to our current Scene(reference)
    std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes;//Vector of Scenes (paired by name and ref)
};