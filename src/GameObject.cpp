#include "GameObject.h"

#include "Globals.h"

GameObject::GameObject(std::string filepath, unsigned int tex_id, glm::vec3 position, glm::vec2 texture_offset, glm::vec3 velocity, float speed)
    :   isEnabled_(false), Object(filepath, tex_id, position, texture_offset), velocity_(velocity), speed_(speed), Destroy_(false)
{

}

GameObject::~GameObject()
{

}

bool GameObject::IsOutOfBounds(glm::vec3& pos) {
    if(pos.x < g_s_ob_left || pos.x > g_s_ob_right)
        return true;
    else return false;
};

void GameObject::Update(float deltaTime) {
    Position_ += (velocity_ * speed_) * deltaTime;
    
    if(IsOutOfBounds(Position_))
        Destroy_ = true;

    
    
    //Update Texture Coords
    
        
};