#pragma once

#include "Object.h"

class GameObject : public Object
{
public:
    GameObject(std::string filepath, unsigned int tex_id, glm::vec3 position,
        glm::vec3 velocity = { 0.0f, 0.0f, 0.0f }, float speed = 1.0f);
    ~GameObject();

private:

    bool isEnabled_;

    float speed_ =  1;
    glm::vec3 velocity_ = {0.0f, 0.0f, 0.0f};

    

public:
    glm::vec3 GetMissleSpawnPoint() { return {Position_.x +  1.0f, Position_.y + 0.5f, 0}; }

    void SetVelocity(glm::vec3 velocity) { velocity_ = velocity; };
    void AdjustVelocity(glm::vec3 velocity) { velocity_ += velocity; };

    void Update(float deltaTime) {
        Position_ += (velocity_ * speed_) * deltaTime;
    };
};