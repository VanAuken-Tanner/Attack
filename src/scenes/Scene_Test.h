#pragma once

#include "Scene.h"

//Game Assets
#include "..\Layer.h"
#include "..\Banner.h"

//engine internal
#include "..\engine\OrthographicCamera.h"
#include "..\engine\TextureManager.h"

//engine external
#include "..\..\deps\external\vendor\glm\glm.hpp"
#include "..\..\deps\external\vendor\glm\gtc\matrix_transform.hpp"



//class for testing scenes only
class Scene_Test : public Scene
{
public:
    Scene_Test();
    ~Scene_Test();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;
    void OnHandleInput();
private:
    
    //private variables
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

    glm::mat4 model_matrix_;
    glm::mat4 Model_view_projection_matrix_;

    //private GAME ASSETS
    GameObject Player_;
    Banner Banner_;
    //====================

    //private functions
    void UpdateBuffers();

};
