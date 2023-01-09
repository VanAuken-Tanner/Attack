#include "Renderer.h"

#include <iostream>

#include "..\Debug.h"

Renderer::Renderer()
{
    Debugger::Log_Console("Renderer Constructor Called.");
}

Renderer::~Renderer()
{

}

void Renderer::Clear() const
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    Clear();
    va.Bind();
    ib.Bind();
    shader.Bind();
    
    GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
