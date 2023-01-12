#include "Scene_Battle.h"

#include <iostream>
#include <string>
#include <vector>

#define BG_LAYER        0
#define CHAR_LAYER      1

static glm::vec3 UpdateCharacterPos_(0,0,0);

Scene_Battle::Scene_Battle()
    :   Translation_(0, 0, 0), CameraTranslation_(0, 0, 0), CreateAtPos_(0,0,0), 
        Background_(BG_LAYER), Characters_(CHAR_LAYER),
        bCreateObject_(false), bUpdateBackground_(true), bUpdateCharacters_(true),
        Camera_(-8.0f, 8.0f, -4.5f, 4.5f) // 16:9 - I guess.. idk how this should be set up...
{
    Debugger<DEBUG_LEVEL>::Log_Console("!!!Constructing Battle!!!");

    vb_layout_.Push<float>(3);//3D coords
    vb_layout_.Push<float>(2);//Texture Coords
    vb_layout_.Push<float>(1);//Texture Slot
    
    BackgoundTexture_ = new Texture(bg_path_, BG_LAYER);
    CharacterTexture_ = new Texture(char_path_, CHAR_LAYER);
    
    Background_.Objects_.push_back(new Object("res/models/Background.obj", BG_LAYER,  0.0f, 0.0f, 0, 1));
    Characters_.Objects_.push_back(new Object("res/models/Character.obj", CHAR_LAYER, 0.0f, 0.0f, 0, 1));

    //Setup our Shader
    std::string sfilepath = "invalid filepath";
    Shader_.Bind();
    Shader_.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    UpdateBuffers();
}

Scene_Battle::~Scene_Battle()
{
    //TODO Delete Layers
}

void Scene_Battle::OnUpdate(float deltaTine)
{
    if(UpdateCharacterPos_.x != 0.0f || UpdateCharacterPos_.y != 0.0f || UpdateCharacterPos_.z != 0.0f)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("UPDATE CHAR POS: (", UpdateCharacterPos_.x, ",", UpdateCharacterPos_.y, ",", UpdateCharacterPos_.z, ")");
        Characters_.Objects_.at(0)->UpdatePosition(UpdateCharacterPos_.x, UpdateCharacterPos_.y, UpdateCharacterPos_.z);
        UpdateBuffers();
        UpdateCharacterPos_ = glm::vec3(0,0,0);
        bUpdateCharacters_ = true;
    }
    
    if(bCreateObject_)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Creating a new object.");
        Object* object = new Object("res/models/TestQuad.obj", CHAR_LAYER, CreateAtPos_.x, CreateAtPos_.y, CreateAtPos_.z, 0.5f);
        Characters_.Objects_.push_back(object);
        
        bCreateObject_ = false;
        CreateAtPos_ = glm::vec3(0,0,0);

        
    }

    // if (bUpdateCharacters_ || bUpdateBackground_)
    //     UpdateBuffers();
}

void Scene_Battle::OnRender()
{

        ModelMatrix_ = glm::translate(glm::mat4(1.0f), Translation_);
        Camera_.SetPosition(CameraTranslation_);
        Model_view_projection_matrix_ = Camera_.GetProjViewMatrix() * ModelMatrix_;
    
        BackgoundTexture_->Bind();
        CharacterTexture_->Bind();
        Shader_.Bind();
        
        Shader_.SetUniform1iv("u_Textures", texture_slots_);
        Shader_.SetUniformMat4fv("u_ModelViewProjection", Model_view_projection_matrix_);
        
        Renderer_.Draw(VertexArray_, IndexBuffer_, Shader_);
}

void Scene_Battle::OnImGuiRender()
{
    ImGui::Begin("Battle Scene Controls");
    Scene::OnImGuiRender();

    // this wants a float arrary so we pass it the address of our first pos in pos array, which is x
    ImGui::SliderFloat3("Translation A", &Translation_.x, -10.0f, 10.f);
    ImGui::SliderFloat3("Camera Position", &CameraTranslation_.x, -10.0f, 10.f);
    //ImGui::SliderFloat1("Camera Rotation", &m_CameraRotation, 0.0f, 100.f);

    ImGui::Separator();
    ImGui::BeginGroup();
    ImGui::SliderFloat3("Position: (x,y,z)", &CreateAtPos_.x, -8.0f, 8.0f);
    bCreateObject_ = ImGui::Button("Create Object");
    ImGui::EndGroup();

    ImGui::End();
}

void Scene_Battle::OnHandleInput(GLFWwindow* window)
{
    GL_CALL(glfwSetKeyCallback(window, key_callback)); 
}

void Scene_Battle::UpdateBuffers()
{
    Debugger<DEBUG_LEVEL>::Log_Console("Updating Buffers...");

    unsigned int curVerticiCount = 0;
    VertexData_.clear();
    Indices_.clear();

    if(Background_.Objects_.size() > 0)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Filling Buffers...", "Background");

        for (int j = 0; j < (int)Background_.Objects_.size(); j++)
        {
            Background_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount == 0 ? 0 : curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Background_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }
        bUpdateBackground_ = false;
    }

    if(Characters_.Objects_.size() > 0)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("Filling Buffers...", "Characters");

        for (int j = 0; j < (int)Characters_.Objects_.size(); j++)
        {
            Characters_.Objects_.at(j)->GetIndiciBufferData(Indices_, curVerticiCount == 0 ? 0 : curVerticiCount);//+0 +4 +8 +12(unsigned int)(m_Positions.size()/5)-1
            curVerticiCount += Characters_.Objects_.at(j)->GetVertexBufferData(VertexData_);
        }     
        bUpdateCharacters_ = false;    
    }

    // Fill our vertex buffer and index buffer with positions and indices
    VertexBuffer_.Update(&VertexData_.at(0), (VertexData_.size() * 5 * sizeof(float))); // size = num posistions * num data in each pos * size of data
    IndexBuffer_.Update(&Indices_.at(0), Indices_.size());
    VertexArray_.AddBuffer(VertexBuffer_, vb_layout_); 
}

void Scene_Battle::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            g_gameState = GameState::Exiting;

        if (key == GLFW_KEY_W && action == GLFW_PRESS)
            UpdateCharacterPos_.y = 0.05f;
        if (key == GLFW_KEY_A && action == GLFW_PRESS)
            UpdateCharacterPos_.x = -0.1f;
        if (key == GLFW_KEY_S && action == GLFW_PRESS)
            UpdateCharacterPos_.y = -0.05f;
        if (key == GLFW_KEY_D && action == GLFW_PRESS)
            UpdateCharacterPos_.x = 0.1f;

        // if (key == GLFW_KEY_W && action == GLFW_PRESS)
        //     UpdateCharacterPos_.y = 0.05f;
        // if (key == GLFW_KEY_A && action == GLFW_PRESS)
        //     UpdateCharacterPos_.x = -0.1f;
        // if (key == GLFW_KEY_S && action == GLFW_PRESS)
        //     UpdateCharacterPos_.y = -0.05f;
        // if (key == GLFW_KEY_D && action == GLFW_PRESS)
        //     UpdateCharacterPos_.x = 0.1f;

        // if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        //     UpdateCharacterPos_.y = 0;
        // if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        //     UpdateCharacterPos_.y = 0;
        // if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        //     UpdateCharacterPos_.x = 0;
        // if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        //     UpdateCharacterPos_.x = 0;
}