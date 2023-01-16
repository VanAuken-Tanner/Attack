#include "GameObject.h"

GameObject::GameObject(std::string filepath, unsigned int tex_id, glm::vec3 position, glm::vec3 velocity, float speed)
    :   isEnabled_(false), Object(filepath, tex_id, position), velocity_(velocity), speed_(speed)
{

}

GameObject::~GameObject()
{

}