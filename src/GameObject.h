#pragma once

#include "Object.h"

class GameObject : public Object
{
public:
    GameObject(std::string filepath, unsigned int tex_id, glm::vec3 position,
        glm::vec3 velocity, float speed);
    ~GameObject();

private:

    bool isEnabled_;

    float speed_ =  1;
    glm::vec3 velocity_ = {0.0f, 0.0f, 0.0f};

public:
    void SetVelocity(glm::vec3 velocity) { velocity_ = velocity; };
    void AdjustVelocity(glm::vec3 velocity) { velocity_ += velocity; };

    void Update(float deltaTime) {
        Position_ += (velocity_ * speed_) * deltaTime;
    };
};