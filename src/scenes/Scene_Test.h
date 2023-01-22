#pragma once

#include "Scene.h"

#include "..\Layer.h"
#include "..\engine\OrthographicCamera.h"
#include "..\engine\Renderer.h"
#include "..\Banner.h"


//class for testing scenes only
class Scene_Test : public Scene
{
public:
    Scene_Test();
    ~Scene_Test();

    void OnUpdate(float deltaTine) override;
    void OnRender() override;
    void OnImGuiRender() override;
    void OnHandleInput();
private:
    void UpdateBuffers();
 
    Banner Banner_;
    
    const int texture_slot_count_ = 2;
    int texture_slots_[2] = {0, 1};

    Shader Shader_;
    Renderer Renderer_;

    OrthographicCamera Camera_;
    glm::vec3 CameraTranslation_;
    float CameraRotation_;
    glm::vec3 Translation_;
    glm::mat4 model_matrix_;
    glm::mat4 Model_view_projection_matrix_;

    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;

    VertexBufferLayout vb_layout_;
    VertexArray VertexArray_;
    VertexBuffer VertexBuffer_;
    IndexBuffer IndexBuffer_;

};
