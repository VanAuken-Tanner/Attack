#include "GameObject.h"

GameObject::GameObject(std::string filepath, unsigned int tex_id, glm::vec3 position, glm::vec2 texture_offset, glm::vec3 velocity, float speed)
    :   isEnabled_(false), Object(filepath, tex_id, position, texture_offset), velocity_(velocity), speed_(speed), Destroy_(false)
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime) {
    Position_ += (velocity_ * speed_) * deltaTime;     
};

void GameObject::UpdateBufferData(std::vector<float>& vertices, std::vector<unsigned int>& inidces, unsigned int& inidicePos)
{
    GetIndiciBufferData(inidces, inidicePos);
    inidicePos += GetVertexBufferData(vertices);
}