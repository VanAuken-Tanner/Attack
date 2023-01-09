#pragma once

#include <iostream>

#include "..\..\deps\external\GLEW\include\GL\glew.h"
#include "..\..\deps\external\GLFW\include\glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
    public:
        Renderer();
        ~Renderer();

        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};