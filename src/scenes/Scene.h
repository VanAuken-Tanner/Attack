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

    // // this wants a float arrary so we pass it the address of our first pos in pos array, which is x
    // ImGui::SliderFloat3("Translation A", &Translation_.x, -10.0f, 10.f);
    // ImGui::SliderFloat3("Camera Position", &CameraTranslation_.x, -10.0f, 10.f);
    // ImGui::SliderFloat("Camera Rotation", &CameraRotation_, 0.0f, 10.0f);

protected:
    Renderer m_Renderer;
};



