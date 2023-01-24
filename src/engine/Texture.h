#pragma once

#include <string>

enum TEXTURE_LAYER
{
    BACKGROUND,
    ENEMY,
    MISSLE,
    PLAYER,
    MENU,//TODO combine banner and text once atlas has background
    TEXT,
    NUM_LAYERS
};

class Texture
{
private:
    std::string Filepath_;
    unsigned int slot_;
    unsigned int RendererID_;
    unsigned char* LocalBuffer_;
    int Width_, Height_, BPP_;

public:
    Texture(std::string& sFilepath, TEXTURE_LAYER slot);
    ~Texture();

    void Bind() const;
    void Unbind() const;


    unsigned int GetWidth() const { return Width_; } 
    unsigned int GetHeight() const { return Height_; }

};

