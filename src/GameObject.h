#pragma once

#include "Object.h"

class GameObject : public Object
{
public:
    GameObject(std::string filepath, unsigned int tex_id, glm::vec3 position,
        glm::vec2 texture_coord_offset = {0.0f, 0.0f},
        glm::vec3 velocity = { 0.0f, 0.0f, 0.0f }, float speed = 1.0f);
    ~GameObject();

private:
    
    glm::vec3 velocity_;
    float speed_;

    bool isEnabled_;
    bool Destroy_;

public:
    void UpdateBufferData(std::vector<float>& vertices, std::vector<unsigned int>& inidces, unsigned int& InidcePos);

    glm::vec3 GetMissleSpawnPoint() { return {Position_.x +  1.0f, Position_.y + 0.5f, 0}; }

    void SetVelocity(glm::vec3 velocity) { velocity_ = velocity; };
    void AdjustVelocity(glm::vec3 velocity) { velocity_ += velocity; };
   
    void Update(float deltaTime);

};