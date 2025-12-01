#include "Scene_Battle.h"

#include <iostream>
#include <string>
#include <vector>


Scene_Battle::Scene_Battle()
    :   Translation_(0, 0, 0), CameraTranslation_(0, 0, 0), CameraRotation_(0), CreateAtPos_(0,0,0), 
        bSpawnEnemy_(false),
        Background_(TEXTURE_LAYER::BACKGROUND),
        Enemies_(TEXTURE_LAYER::ENEMY),
        Projectiles_(TEXTURE_LAYER::MISSLE),
        Player_("res/models/Character.obj", TEXTURE_LAYER::PLAYER, {-2.0f, -1.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f }, 3),
        Banner_(),
        Camera_(screen_left_, screen_right_, screen_bottom_, screen_top_) 
{

    vb_layout_.Push<float>(3);//3D coords
    vb_layout_.Push<float>(2);//Texture Coords
    vb_layout_.Push<float>(1);//Texture Slot
    
    Background_.Objects_.push_back(new GameObject("res/models/Background.obj", TEXTURE_LAYER::BACKGROUND, {0.0f, 0.0f, 0.0f}));

    std::string msg = "abcdefghijklmnopqrstuvwxyz0123456789";
    Banner_.SetText(msg);

    //Setup our Shader
    Shader_.Bind();
    Shader_.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    
    SetKeyActions();
}

Scene_Battle::~Scene_Battle()
{

}

void Scene_Battle::OnUpdate(float deltaTime)
{
    Player_.Update(deltaTime);

    if(bSpawnEnemy_)
    {
        Enemies_.Objects_.push_back(new GameObject("res/models/Character.obj", TEXTURE_LAYER::ENEMY, CreateAtPos_));
        bSpawnEnemy_ = false;
    }

    for (GameObject* missle : Projectiles_.Objects_)
        missle->Update(deltaTime);

    Camera_.SetPosition(CameraTranslation_);
    Camera_.SetRotation(CameraRotation_);
    UpdateBuffers();
}

void Scene_Battle::OnRender()
{
    m_Renderer.Clear();

    ModelMatrix_ = glm::translate(glm::mat4(1.0f), Translation_);
    Model_view_projection_matrix_ = Camera_.GetProjViewMatrix() * ModelMatrix_;

    TextureManager_.BindTextures();
    
    Shader_.Bind();
    
    Shader_.SetUniform1iv("u_Textures", TextureManager_.GetTextureSlots(), TextureManager_.GetNumTextureSlots());
    Shader_.SetUniformMat4fv("u_ModelViewProjection", Model_view_projection_matrix_);
    
    Renderer_.Draw(VertexArray_, IndexBuffer_, Shader_);
}

void Scene_Battle::OnImGuiRender()
{
    ImGui::Begin("Battle Scene Controls");
    Scene::OnImGuiRender();

    

    //ImGui::Separator();


    ImGui::BeginGroup();

    if(ImGui::Button("Spawn Horde"))
        SpawnWave();
        
    if(ImGui::Button("Clear Horde"))
        ClearWave();

    ImGui::Separator();
    
    bSpawnEnemy_ = ImGui::Button("Spawn Enemy");
    ImGui::SliderFloat3("Position: (x,y,z)", &CreateAtPos_.x, -8.0f, 8.0f);

    ImGui::EndGroup();

    ImGui::End();
}

void Scene_Battle::SpawnWave()
{
    int num_goblins_ = RNG::GetRandInt(2,6);
    std::vector<glm::vec3> positions;

    LOG_2("Num goblins = ", num_goblins_);

    for(int i = 0; i < (int)num_goblins_; i ++)
        positions.push_back({RNG::GetRandFloat(1.0f,6.0f), RNG::GetRandFloat(-4.0f,1.0f), 0});

    for(int i = 0; i < (int)positions.size(); i++)
        Enemies_.Objects_.push_back(new GameObject("res/models/Character.obj", TEXTURE_LAYER::ENEMY, positions.at(i)));
}

void Scene_Battle::OnHandleInput()
{
    InputHandler::HandleKeyEvents();
}

void Scene_Battle::UpdateBuffers()
{
    unsigned int curVerticiCount = 0;
    VertexData_.clear();
    Indices_.clear();

    if(Background_.Objects_.size() > 0)
    {
        for (int j = 0; j < (int)Background_.Objects_.size(); j++)
        {
            Background_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Background_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
    }
    
    
    Player_.GetIndiciBufferData(Indices_, curVerticiCount);
    curVerticiCount += Player_.GetVertexBufferData(VertexData_);

    if(Enemies_.Objects_.size() > 0)
    {
        for (int j = 0; j < (int)Enemies_.Objects_.size(); j++)
        {
            Enemies_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Enemies_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
    }

    if(Projectiles_.Objects_.size() > 0)
    {
        for (int j = 0; j < (int)Projectiles_.Objects_.size(); j++)
        {
            Projectiles_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Projectiles_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
    }

    Banner_.UpdateBufferData(VertexData_, Indices_, curVerticiCount);


    // Fill our vertex buffer and index buffer with positions and indices
    VertexBuffer_.Update(&VertexData_.at(0), (VertexData_.size() * vb_layout_.GetStride() * sizeof(float))); // size = count * stride * size of data(only using floats)
    IndexBuffer_.Update(&Indices_.at(0), Indices_.size());
    VertexArray_.AddBuffer(VertexBuffer_, vb_layout_); 
}

void Scene_Battle::SetKeyActions()
{
    InputHandler::AddKeyAction<GLFW_KEY_E>([this](bool pressed) {
        if(pressed)
        {
            LOG_1("Spawning missle...")
            Projectiles_.Objects_.push_back(new GameObject("res/models/Missle.obj", TEXTURE_LAYER::MISSLE, Player_.GetMissleSpawnPoint(), {0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f }, 4));
        }
    });

    InputHandler::AddKeyAction<GLFW_KEY_W>( [this](bool pressed) { 
        if(pressed)
            Player_.AdjustVelocity({0.0f, 1.0f, 0.0f});
        else
            Player_.AdjustVelocity({0.0f, -1.0f, 0.0f});
    });

    InputHandler::AddKeyAction<GLFW_KEY_A>( [this](bool pressed) {
        if(pressed)
            Player_.AdjustVelocity({-1.0f, 0.0f, 0.0f}); 
        else
            Player_.AdjustVelocity({1.0f, 0.0f, 0.0f});     
    });

    InputHandler::AddKeyAction<GLFW_KEY_S>( [this](bool pressed) { 
        if(pressed)
            Player_.AdjustVelocity({0.0f, -1.0f, 0.0f});
        else
            Player_.AdjustVelocity({0.0f, 1.0f, 0.0f});
    });

    InputHandler::AddKeyAction<GLFW_KEY_D>( [this](bool pressed) { 
        if(pressed)
            Player_.AdjustVelocity({1.0f, 0.0f, 0.0f}); 
        else
            Player_.AdjustVelocity({-1.0f, 0.0f, 0.0f});     
    });
}