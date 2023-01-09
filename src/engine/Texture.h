#pragma once

#include <string>

class Texture
{
private:
    std::string Filepath_;
    unsigned int slot_;
    unsigned int RendererID_;
    unsigned char* LocalBuffer_;
    int Width_, Height_, BPP_;

public:
    Texture(std::string& sFilepath, int slot);
    ~Texture();

    void Bind() const;
    void Unbind() const;


    unsigned int GetWidth() const { return Width_; } 
    unsigned int GetHeight() const { return Height_; }

};

