#pragma once

#include <vector>
#include <string>
#include <functional>

#include "..\..\deps\external\vendor\imgui\imgui.h"

#include "..\Debug.h"

#include "..\engine\Renderer.h"
#include "..\engine\Texture.h"
#include "..\engine\Shader.h"
#include "..\InputHandler.h"


class Scene
{
private: 

protected:
    bool exit_scene_;
    bool close_game_;
    Renderer m_Renderer;

    float screen_left_ = -8.0f;
    float screen_right_ = 8.0f;
    float screen_bottom_ = -4.5f;
    float screen_top_ = 4.5f;
    float screen_ob_left_ = -16.0f;
    float screen_ob_right_ = 16.0f;
    float screen_ob_bottom_ = -9.0f;
    float screen_ob_top_ = 9.0f;
    
public:
    Scene(/* args */) { exit_scene_ = false; close_game_ = false; }
    virtual ~Scene() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender();
    virtual void OnHandleInput() {}
    bool ExitingScene() { return exit_scene_; }
    bool ClosingGame() {return close_game_; }
    
};



