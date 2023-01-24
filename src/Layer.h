#pragma once

#include <vector>

#include "engine\Renderer.h"
#include "engine\Texture.h"
#include "GameObject.h"


class Layer
{
public:

    Layer(unsigned int textureID) { TextureID_ = textureID; }
    ~Layer();

    unsigned int TextureID_;
    unsigned int TextureID_BANNER_;
    
    std::vector<GameObject*> Objects_;

    std::vector<float> VertexData_;
    std::vector<unsigned int> Indices_;


};