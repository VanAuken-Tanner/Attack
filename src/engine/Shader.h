#pragma once

#include <string>
#include <unordered_map>

#include "..\..\deps\external\vendor\glm\glm.hpp"



class Shader
{
private:
    std::string m_sFilepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_mUniformLocationCache;


public:
    Shader();
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //Set uniforms
    void SetUniform1i(const std::string& name, int value); 
    void SetUniform1iv(const std::string& name, int* values, int size); 
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4fv(const std::string& name, glm::mat4& matrix);
    
private:
    std::string ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    int GetUniformLocation(const std::string& name);
};