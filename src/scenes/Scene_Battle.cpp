#include "Scene_Battle.h"

#include <iostream>
#include <string>
#include <vector>


Scene_Battle::Scene_Battle()
    :   Translation_(0, 0, 0), CameraTranslation_(0, 0, 0), CreateAtPos_(0,0,0), 
        Background_(BG_LAYER),
        Enemies_(ENEMY_LAYER), bSpawnEnemy_(false),
        Projectiles_(MISSLE_LAYER),
        Player_("res/models/Character.obj", PLAYER_LAYER, {-2.0f, -1.0f, 0.0f}, { 0.0f, 0.0f, 0.0f }, 3),
        Camera_(-8.0f, 8.0f, -4.5f, 4.5f) 
{
    Debugger<DEBUG_LEVEL>::Log_Console("!!!Constructing Battle!!!");

    vb_layout_.Push<float>(3);//3D coords
    vb_layout_.Push<float>(2);//Texture Coords
    vb_layout_.Push<float>(1);//Texture Slot
    
    //BackgoundTexture_ = new Texture(bg_path_, BG_LAYER);
    BackgoundTexture_ = new Texture(bg_path_, BG_LAYER);
    PlayerTexture_ = new Texture(char_path_, PLAYER_LAYER);
    EnemyTexture_ = new Texture(enemy_path_, ENEMY_LAYER);
    ProjectileTexture_ = new Texture(projectile_path_, MISSLE_LAYER);
    
    Background_.Objects_.push_back(new GameObject("res/models/Background.obj", BG_LAYER, {0.0f, 0.0f, 0.0f}));

    //Setup our Shader
    std::string sfilepath = "invalid filepath";
    Shader_.Bind();
    Shader_.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    
    SetKeyActions();
}

Scene_Battle::~Scene_Battle()
{
    delete BackgoundTexture_;
    delete PlayerTexture_;
    delete EnemyTexture_;
    delete ProjectileTexture_;


}

void Scene_Battle::OnUpdate(float deltaTime)
{
    Player_.Update(deltaTime);
    if(bSpawnEnemy_)
    {
        Enemies_.Objects_.push_back(new GameObject("res/models/Character.obj", ENEMY_LAYER, CreateAtPos_));
        bSpawnEnemy_ = false;
    }
    for (GameObject* missle : Projectiles_.Objects_)
        missle->Update(deltaTime);
    //Projectiles_.Objects_.at(0)->Update(deltaTime);

    Camera_.SetPosition(CameraTranslation_);
    Camera_.SetRotation(CameraRotation_);
    UpdateBuffers();
}

void Scene_Battle::OnRender()
{
    ModelMatrix_ = glm::translate(glm::mat4(1.0f), Translation_);
    Model_view_projection_matrix_ = Camera_.GetProjViewMatrix() * ModelMatrix_;

    BackgoundTexture_->Bind();
    PlayerTexture_->Bind();
    EnemyTexture_->Bind();
    ProjectileTexture_->Bind();
    
    Shader_.Bind();
    
    Shader_.SetUniform1iv("u_Textures", texture_slots_);
    Shader_.SetUniformMat4fv("u_ModelViewProjection", Model_view_projection_matrix_);
    
    Renderer_.Draw(VertexArray_, IndexBuffer_, Shader_);
}

void Scene_Battle::OnImGuiRender()
{
    ImGui::Begin("Battle Scene Controls");
    Scene::OnImGuiRender();

    // // this wants a float arrary so we pass it the address of our first pos in pos array, which is x
    // ImGui::SliderFloat3("Translation A", &Translation_.x, -10.0f, 10.f);
    // ImGui::SliderFloat3("Camera Position", &CameraTranslation_.x, -10.0f, 10.f);
    // ImGui::SliderFloat("Camera Rotation", &CameraRotation_, 0.0f, 10.0f);

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

    for(int i = 0; i < num_goblins_; i ++)
        positions.push_back({RNG::GetRandFloat(1.0f,6.0f), RNG::GetRandFloat(-4.0f,1.0f), 0});

    for(int i = 0; i < positions.size(); i++)
        Enemies_.Objects_.push_back(new GameObject("res/models/Character.obj", ENEMY_LAYER, positions.at(i)));
}

void Scene_Battle::OnHandleInput()
{
    if(!InputHandler::GetIsKeyHandled('w'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('w'));
            InputHandler::SetKeyHandled('w');
            
        }

        if(!InputHandler::GetIsKeyHandled('a'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('a'));
            InputHandler::SetKeyHandled('a');
            
        }

        if(!InputHandler::GetIsKeyHandled('s'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('s'));
            InputHandler::SetKeyHandled('s');
            
        }

        if(!InputHandler::GetIsKeyHandled('d'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('d'));
            InputHandler::SetKeyHandled('d');
            
        }

        if(!InputHandler::GetIsKeyHandled('e'))
        {
            InputHandler::QueueAction(InputHandler::GetKeyAction('e'));
            InputHandler::SetKeyHandled('e');
            
        }

        if(InputHandler::GetActionCount() > 0)
        {
            InputHandler::ExecuteActions();        
            //ASSERT(false);
        }
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
            Background_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount == 0 ? 0 : curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Background_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
    }
    Player_.GetIndiciBufferData(Indices_, curVerticiCount == 0 ? 0 : curVerticiCount);
    curVerticiCount += Player_.GetVertexBufferData(VertexData_);

    if(Enemies_.Objects_.size() > 0)
    {
        for (int j = 0; j < (int)Enemies_.Objects_.size(); j++)
        {
            Enemies_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount == 0 ? 0 : curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Enemies_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
    }

    if(Projectiles_.Objects_.size() > 0)
    {
        for (int j = 0; j < (int)Projectiles_.Objects_.size(); j++)
        {
            Projectiles_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount == 0 ? 0 : curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Projectiles_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
    }


    // Fill our vertex buffer and index buffer with positions and indices
    VertexBuffer_.Update(&VertexData_.at(0), (VertexData_.size() * vb_layout_.GetStride() * sizeof(float))); // size = count * stride * size of data(only using floats)
    IndexBuffer_.Update(&Indices_.at(0), Indices_.size());
    VertexArray_.AddBuffer(VertexBuffer_, vb_layout_); 
}

void Scene_Battle::SetKeyActions()
{
    InputHandler::AddKeyAction<'e'>([this](bool pressed) {
        if(pressed)
        {
            LOG_1("Spawning missle...")
            Projectiles_.Objects_.push_back(new GameObject("res/models/Missle.obj", MISSLE_LAYER, Player_.GetMissleSpawnPoint(),{ 1.0f, 0.0f, 0.0f }, 4));
        }
    });

    InputHandler::AddKeyAction<'w'>( [this](bool pressed) { 
        if(pressed)
            Player_.AdjustVelocity({0.0f, 1.0f, 0.0f});
        else
            Player_.AdjustVelocity({0.0f, -1.0f, 0.0f});
    });

    InputHandler::AddKeyAction<'a'>( [this](bool pressed) {
        if(pressed)
            Player_.AdjustVelocity({-1.0f, 0.0f, 0.0f}); 
        else
            Player_.AdjustVelocity({1.0f, 0.0f, 0.0f});     
    });

    InputHandler::AddKeyAction<'s'>( [this](bool pressed) { 
        if(pressed)
            Player_.AdjustVelocity({0.0f, -1.0f, 0.0f});
        else
            Player_.AdjustVelocity({0.0f, 1.0f, 0.0f});
    });

    InputHandler::AddKeyAction<'d'>( [this](bool pressed) { 
        if(pressed)
            Player_.AdjustVelocity({1.0f, 0.0f, 0.0f}); 
        else
            Player_.AdjustVelocity({-1.0f, 0.0f, 0.0f});     
    });
}