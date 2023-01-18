#pragma once

#include "Scene.h"

#include "..\Layer.h"
#include "..\GameObject.h"
#include "..\engine\OrthographicCamera.h"

#include "..\..\deps\external\vendor\glm\glm.hpp"
#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"

#define BG_LAYER        0
#define PLAYER_LAYER    1
#define ENEMY_LAYER     2
#define MISSLE_LAYER    3

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
private://member variables

    std::string bg_path_ = "res/art/Mountains.png";
    std::string enemy_path_ = "res/art/goblin.png";
    std::string char_path_ = "res/art/Wizard.png";
    std::string projectile_path_ = "res/art/blue_square_25a.png";
    
    glm::vec3 Translation_;
    glm::vec3 CameraTranslation_;
    float CameraRotation_;
    glm::vec3 CreateAtPos_;

    bool bSpawnEnemy_;
    
    Layer Background_;
    Layer Enemies_;
    Layer Projectiles_;
    GameObject Player_;

    Texture* BackgoundTexture_;
    Texture* PlayerTexture_;
    Texture* EnemyTexture_;
    Texture* ProjectileTexture_;

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
    int texture_slots_[4] = { 0, 1, 2, 3 };

    void SetKeyActions();
    void UpdateBuffers();

    void SpawnWave();
    void ClearWave() { Enemies_.Objects_.clear(); }

    //debug helper
    void PrintDetails();
};
