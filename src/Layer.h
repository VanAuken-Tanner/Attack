#pragma once

#include <vector>

#include "engine\Renderer.h"
#include "engine\Texture.h"
#include "Object.h"


class Layer
{
public:

    Layer(unsigned int textureID) { TextureID_ = textureID; }
    ~Layer();

    // void Draw();//not impl
    // void PrintDetails();

    //LayerLevel layerLevel_;

    //Texture* Texture_;
    unsigned int TextureID_;
    std::vector<Object*> Objects_;
    std::vector<float> VertexData_;
    std::vector<unsigned int> Indices_;

    // VertexArray VertexArray_;
    // VertexBuffer VertexBuffer_;
    // IndexBuffer IndexBuffer_;
};