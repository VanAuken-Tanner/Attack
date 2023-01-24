#pragma once

#include "Debug.h"

#include "Layer.h"
#include "engine\Texture.h"

class Banner
{
public:
    Banner();
    ~Banner() {}

    void SetText(std::string& msg);
    void UpdateBufferData(std::vector<float>& vertices, std::vector<unsigned int>& inidces, unsigned int& InidcePos);

private:
    
    Layer Banner_;
    Layer Text_;

    const glm::vec2 text_coord_offset_ = {16.0f, 0.0f};
    const glm::vec3 text_pos_root_ = {-7.0f, -3.0f, 0.0f};
    const glm::vec3 text_pos_offset_ = {0.15f, 0.0f, 0.0f};

    glm::vec2 GetTextureCoords(char val);
};