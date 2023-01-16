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
    bool exit_;
    
public:
    Scene(/* args */) { exit_ = false; }
    virtual ~Scene() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender();
    virtual void OnHandleInput() {}
    bool Exiting() { return exit_; }

protected:
    Renderer m_Renderer;
};



