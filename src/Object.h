#pragma once

#include <vector>
#include <string>
#include "..\deps\external\vendor\glm\glm.hpp"

#include "Debug.h"


struct Face
{
    unsigned int v,vt,vn;
};

class Object// : public GameObject
{
private:
    unsigned int textureId_; 
    std::string ObjFilepath_;

protected:
    glm::vec3 Position_;
    
public:
    Object(std::string filepath, unsigned int tex_id, glm::vec3 position);
    ~Object();

    std::vector<glm::vec3> Vertices_;
    std::vector<glm::vec2> TextureVerticies_;

    std::vector<unsigned int> Indices_;
    std::vector<unsigned int> TextureIndices_;

    //void UpdatePos();
    void LoadObjectFromOBJ(std::string& filepath);

    //debug helpers
    const void PrintAll();
    const void PrintVertices();
    const void PrintTextureVertices();
    const void PrintIndices();
    const void PrintTextureIndices();
    
    //loads the vertex and index data into the buffers and returns the number added
    unsigned int GetVertexBufferData(std::vector<float>& vertex_buffer);
    unsigned int GetIndiciBufferData(std::vector<unsigned int>& index_buffer, unsigned int start);
};

