#include "IndexBuffer.h"
#include "Renderer.h"

#include "..\Debug.h"

IndexBuffer::IndexBuffer()
{
    m_Count = 0;
    GL_CALL(glGenBuffers(1, &m_RendererID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER , m_Count * sizeof(unsigned int), nullptr, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GL_CALL(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Update(const unsigned int* data, unsigned int count)
{
    m_Count = count;
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER , count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
};

void IndexBuffer::Unbind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};