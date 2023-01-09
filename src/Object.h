#pragma once

#include <vector>
#include <string>

struct Point
{
    float x, y, z;
};

struct Face
{
    unsigned int v,vt,vn;
};

class Object// : public GameObject
{
private:
unsigned int textureId_; 
    float m_xpos;
    float m_ypos;
    float m_zpos;
    float m_scale;

    void UpdatePos();
    void LoadObjectFromOBJ(std::string filepath);
    
public:
    Object(std::string filepath, unsigned int tex_id, float xpos = 0, float ypos = 0, float zpos = 0, float scale = 1.0f);
    ~Object();

    std::vector<Point> m_Points;
    std::vector<Point> m_TexturePoints;
    //std::vector<Face>  m_Faces; - not implemented
    std::vector<unsigned int> m_Indices;
    std::vector<unsigned int> m_TextureIndices;

    const unsigned int GetNumVerts();

    //debug helpers
    const void PrintAll();
    const void PrintVertices();
    const void PrintTextureVertices();
    const void PrintIndices();
    const void PrintTextureIndices();
    
    //loads the vertex and index data into the buffers and returns the number added
    unsigned int GetVertexBufferData(std::vector<float>& vertex_buffer);
    unsigned int GetIndiciBufferData(std::vector<unsigned int>& index_buffer, unsigned int start);

    void UpdatePosition(float xpos, float ypos, float zpos);
};

