#pragma once

#include "Scene.h"

#include "..\Layer.h"
#include "..\Banner.h"
#include "..\GameObject.h"
#include "..\engine\OrthographicCamera.h"

#include "..\engine\TextureManager.h"

#include "..\..\deps\external\vendor\glm\glm.hpp"
#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"

#include <random>

class RNG
{
public:
    static inline int GetRandInt(int min, int max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [1, 6]

        
        return dist(rng);
    }

    static inline int GetRandFloat(float min, float max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<float> dist(min, max);

        return dist(rng);
    }
};


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

    bool bSpawnEnemy_;
    glm::vec3 CreateAtPos_;
    
    Layer Background_;
    Layer Enemies_;
    Layer Projectiles_;
    GameObject Player_;
    Banner Banner_;

    TextureManager TextureManager_;
    Shader Shader_;
    Renderer Renderer_;

    std::vector<float> VertexData_;
    std::vector<unsigned int> Indices_;

    VertexBufferLayout vb_layout_;
    VertexArray VertexArray_;
    VertexBuffer VertexBuffer_;
    IndexBuffer IndexBuffer_;

    OrthographicCamera Camera_;
    glm::mat4 ModelMatrix_;
    glm::mat4 Model_view_projection_matrix_;// = projectionMatrix * viewMatrix * modelMatrix;

    void SetKeyActions();
    void UpdateBuffers();

    void SpawnWave();
    inline void ClearWave() { Enemies_.Objects_.clear(); }

    //debug helper
    void PrintDetails();
};
