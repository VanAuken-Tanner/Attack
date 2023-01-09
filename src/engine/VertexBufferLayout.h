#pragma once

#include <vector>

#include "..\..\deps\external\GLEW\include\GL\glew.h"

//3 vecs for vertex pos
//2 vecs for texture vertex pos
struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:              return sizeof(GL_FLOAT);
            case GL_UNSIGNED_INT:       return sizeof(GL_UNSIGNED_INT);
            case GL_UNSIGNED_BYTE:      return sizeof(GL_UNSIGNED_BYTE);
        }
        
        return 0;

    }
};


class VertexBufferLayout
{
public:
VertexBufferLayout()
        : m_Stride(0) {}
    //~VertexBufferLayout();


private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:

    template<typename T>
    void Push(unsigned int count)
    {
        //static_assert(false);
    }

    inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements; }
    inline unsigned int GetStride() const {return m_Stride; }
};

template<> inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back((VertexBufferElement){GL_FLOAT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<> inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back((VertexBufferElement){GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<> inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back((VertexBufferElement){GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}