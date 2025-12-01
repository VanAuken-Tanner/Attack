#include "Scene_Test.h"

#include "..\Debug.h"

Scene_Test::Scene_Test()
    :   Translation_(0, 0, 0), CameraTranslation_(0, 0, 0), CameraRotation_(0), CreateAtPos_(0,0,0),
        Banner_(),
        Player_("res/models/Character.obj", TEXTURE_LAYER::PLAYER, {-2.0f, -1.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f }, 3),
        Camera_(screen_left_, screen_right_, screen_bottom_, screen_top_)
{
    LOG_1("Constructing Testing Scene.");

    vb_layout_.Push<float>(3);
    vb_layout_.Push<float>(2);
    vb_layout_.Push<float>(1);
    
    std::string msg = "i.love.you.abby";
    Banner_.SetText(msg);

    Shader_.Bind();
    Shader_.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

}

Scene_Test::~Scene_Test()
{

}

void Scene_Test::OnUpdate(float deltaTime)
{
    Player_.Update(deltaTime);

    Camera_.SetPosition(CameraTranslation_);
    Camera_.SetRotation(CameraRotation_);
    UpdateBuffers();
}

void Scene_Test::OnRender()
{
    m_Renderer.Clear();

    model_matrix_ = glm::translate(glm::mat4(1.0f), Translation_);
    Model_view_projection_matrix_ = Camera_.GetProjViewMatrix() * model_matrix_;

    TextureManager_.BindTextures();

    Shader_.Bind();
    
    Shader_.SetUniform1iv("u_Textures", TextureManager_.GetTextureSlots(), TextureManager_.GetNumTextureSlots());
    Shader_.SetUniformMat4fv("u_ModelViewProjection", Model_view_projection_matrix_);

    Renderer_.Draw(VertexArray_, IndexBuffer_, Shader_);
}

void Scene_Test::OnImGuiRender()
{
    Scene::OnImGuiRender();
    ImGui::Begin("Test Scene:");
    
    ImGui::End();
}

void Scene_Test::OnHandleInput()
{
    
}

void Scene_Test::UpdateBuffers()
{
    unsigned int curVerticiCount = 0;
    VertexData_.clear();
    Indices_.clear();
    
    Banner_.UpdateBufferData(VertexData_, Indices_, curVerticiCount);
    Player_.UpdateBufferData(VertexData_, Indices_, curVerticiCount);

    LOG_1("OnUpdatedBuffers...");
    LOG_2("Vertices: ", VertexData_.size());
    LOG_2("Index Buffer Count: ", Indices_.size());
  

    VertexBuffer_.Update(&VertexData_.at(0), VertexData_.size() * vb_layout_.GetStride() * sizeof(float));
    IndexBuffer_.Update(&Indices_.at(0), Indices_.size());
    VertexArray_.AddBuffer(VertexBuffer_, vb_layout_);
}
