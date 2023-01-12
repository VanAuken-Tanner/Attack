#include "VertexArray.h"

#include "Renderer.h"

#include "..\Debug.h"

VertexArray::VertexArray()
{
    GL_CALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GL_CALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    GL_CALL(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GL_CALL(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        Debugger<DEBUG_LEVEL>::Log_Console("VA - Adding Element (", i, ")");
        
        const auto& element = elements[i];
        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type,
            element.normalized, layout.GetStride(), reinterpret_cast<void*>(offset)));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}
