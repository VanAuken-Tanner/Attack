#include "Scene_Test.h"

#include "..\Debug.h"
#include "..\Globals.h"



Scene_Test::Scene_Test()
    :   Translation_(0, 0, 0),
        Camera_(g_s_left, g_s_right, g_s_bottom, g_s_top)
{
    Debugger<DEBUG_LEVEL>::Log_Console("Constructing Testing Scene.");

    vb_layout_.Push<float>(3);
    vb_layout_.Push<float>(2);
    vb_layout_.Push<float>(1);

    Shader_.Bind();
    Shader_.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    
    std::string msg = "hello.dom..how.are.you?";
    Banner_.SetText(msg);

}

Scene_Test::~Scene_Test()
{

}

void Scene_Test::OnUpdate(float deltaTine)
{
    //Debugger<DEBUG_LEVEL>::Log_Console("Updating...");
    Camera_.SetPosition({0.0f,0.0f,0.0f});
    UpdateBuffers();
}

void Scene_Test::OnRender()
{
    //Debugger<DEBUG_LEVEL>::Log_Console("Rendering...");
    m_Renderer.Clear();

    model_matrix_ = glm::translate(glm::mat4(1.0f), Translation_);
    Model_view_projection_matrix_ = Camera_.GetProjViewMatrix() * model_matrix_;

    ;

    Shader_.Bind();
    
    Shader_.SetUniform1iv("u_Textures", texture_slots_, texture_slot_count_);
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
    int IndiciPos = 0;
    vertices_.clear();
    indices_.clear();
    
    //Banner_.UpdateBufferData(vertices_, indices_, IndiciPos);

    // LOG_1("OnUpdatedBuffers...");
    // LOG_2("Vertices: ", vertices_.size());
    // LOG_2("Index Buffer Count: ", indices_.size());
    //ASSERT(false);

    VertexBuffer_.Update(&vertices_.at(0), vertices_.size() * vb_layout_.GetStride() * sizeof(float));
    IndexBuffer_.Update(&indices_.at(0), indices_.size());
    VertexArray_.AddBuffer(VertexBuffer_, vb_layout_);
}
