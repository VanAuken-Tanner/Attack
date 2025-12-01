#pragma once

#include "Scene.h"

#include "..\Layer.h"
#include "..\Banner.h"
#include "..\GameObject.h"
#include "..\engine\OrthographicCamera.h"

#include "..\engine\TextureManager.h"

#include "..\..\deps\external\vendor\glm\glm.hpp"
#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"

#include "..\RNG.h"


class Scene_Battle : public Scene
{
public:
    Scene_Battle();
    ~Scene_Battle();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
    void OnHandleInput() override;

private://member variables

    glm::vec3 Translation_;
    glm::vec3 CameraTranslation_;
    float CameraRotation_;
    glm::vec3 CreateAtPos_;

    TextureManager TextureManager_;
    Shader Shader_;
    Renderer Renderer_;
    OrthographicCamera Camera_;

    VertexBufferLayout vb_layout_;
    VertexArray VertexArray_;
    VertexBuffer VertexBuffer_;
    IndexBuffer IndexBuffer_;

    std::vector<float> VertexData_;
    std::vector<unsigned int> Indices_;
    
    glm::mat4 ModelMatrix_;
    glm::mat4 Model_view_projection_matrix_;// = projectionMatrix * viewMatrix * modelMatrix;

    //private GAME ASSETS
    Layer Background_;
    Layer Enemies_;
    Layer Projectiles_;
    GameObject Player_;
    Banner Banner_;
    //====================


    bool bSpawnEnemy_;

    void SetKeyActions();
    void UpdateBuffers();

    void SpawnWave();
    inline void ClearWave() { Enemies_.Objects_.clear(); }

    //debug helper
    void PrintDetails();
};
