#pragma once

#include "Scene.h"

#include "..\Layer.h"
#include "..\GameObject.h"
#include "..\engine\OrthographicCamera.h"

#include "..\..\deps\external\vendor\glm\glm.hpp"
#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"

class Scene_Battle : public Scene
{
private://member variables

    std::string bg_path_ = "res/art/Mountains.png";
    std::string enemy_path_ = "res/art/red_square.png";
    std::string char_path_ = "res/art/Wizard.png";
    
    glm::vec3 Translation_;
    glm::vec3 CameraTranslation_;
    float CameraRotation_;
    glm::vec3 CreateAtPos_;

    bool bSpawnEnemy_;
    
    Layer Background_;
    Layer Enemies_;
    GameObject Player_;

    Texture* BackgoundTexture_;
    Texture* PlayerTexture_;
    Texture* EnemyTexture_;

    Renderer Renderer_;
    Shader Shader_;

    VertexBufferLayout vb_layout_;
    std::vector<float> VertexData_;
    std::vector<unsigned int> Indices_;

    VertexArray VertexArray_;
    VertexBuffer VertexBuffer_;
    IndexBuffer IndexBuffer_;

    OrthographicCamera Camera_;
    glm::mat4 ModelMatrix_;
    glm::mat4 Model_view_projection_matrix_;// = projectionMatrix * viewMatrix * modelMatrix;

public:
    Scene_Battle();
    ~Scene_Battle();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
    void OnHandleInput() override;

private:
    int texture_slots_[3] = { 0, 1, 2 };

    void SetKeyActions();
    void UpdateBuffers();

    //debug helper
    void PrintDetails();
};
