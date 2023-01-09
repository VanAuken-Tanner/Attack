#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

#include "..\Debug.h"

Shader::Shader()
    : m_RendererID(0)
{
    //hardcoded shader paths for now
    std::string vertexShader = ParseShader("res/shaders/vertex.shader");
    std::string fragmentShader = ParseShader("res/shaders/fragment.shader");

    CreateShader(vertexShader, fragmentShader);
    Bind();
}

Shader::~Shader()
{

}

std::string Shader::ParseShader(const std::string& filepath)
{
    std::string shader;
    std::ifstream stream(filepath);
    std::string line = "";

    while (getline(stream, line))
    {
        shader += line;
        shader += "\n";
    }
    
    return shader;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    //https://www.youtube.com/watch?v=71BLZwRGUJE&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=7
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char;

        glGetShaderInfoLog(id, length, &length, message);
        Debugger::Log_Console("Failed to compile Shader");
        Debugger::Log_Console((type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        Debugger::Log_Console(message);
        glDeleteShader(id);

        delete message;
        return 0;
    }

    Debugger::Log_Console("Shader Compiled...");

    return id;
}


void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    m_RendererID = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);

    glDeleteShader(vs);
    glDeleteShader(fs);

    ASSERT(m_RendererID != 0);
    
}


void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GL_CALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1iv(const std::string& name, int* values)
{
    GL_CALL(glUniform1iv(GetUniformLocation(name), 2, values));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GL_CALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4fv(const std::string& name, glm::mat4& matrix)
{
    GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if(m_mUniformLocationCache.find(name) != m_mUniformLocationCache.end())
        return m_mUniformLocationCache[name];

    GL_CALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    m_mUniformLocationCache[name] = location;
    
    return location;
} 