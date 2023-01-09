#pragma once

#include "Scene.h"

#include "..\Layer.h"
#include "..\engine\OrthographicCamera.h"

#include "..\..\deps\external\vendor\glm\glm.hpp"
#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"

class Scene_Battle : public Scene
{
private://member variables

    std::string bg_path_ = "res/art/Mountains.png";
    std::string char_path_ = "res/art/Wizard.png";
    
    glm::vec3 Translation_;
    glm::vec3 CameraTranslation_;
    glm::vec3 CreateAtPos_;
    
    
    Layer Background_;
    Layer Characters_;

    bool bCreateObject_;
    bool bUpdateBackground_;
    bool bUpdateCharacters_;

    Renderer Renderer_;
    Shader Shader_;
    Texture* BackgoundTexture_;
    Texture* CharacterTexture_;

    std::vector<float> VertexData_;
    std::vector<unsigned int> Indices_;

    VertexBufferLayout vb_layout_;

    VertexArray VertexArray_;
    VertexBuffer VertexBuffer_;
    IndexBuffer IndexBuffer_;

    OrthographicCamera Camera_;
    glm::mat4 ModelMatrix_;
    glm::mat4 Model_view_projection_matrix_;// = projectionMatrix * viewMatrix * modelMatrix;

public:
    Scene_Battle();
    ~Scene_Battle();

    void OnUpdate(float deltaTine) override;
    void OnRender() override;
    void OnImGuiRender() override;
    void OnHandleInput(GLFWwindow* window) override;

private:
    int texture_slots_[2] = { 0, 1 };

    void UpdateBuffers();
    void PrintDetails();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

};
