#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include "..\..\deps\external\vendor\stb_image\stb_image.h"

#include "..\Debug.h"

#include "Renderer.h"

Texture::Texture(std::string& filepath, TEXTURE_LAYER slot)
    :   Filepath_(filepath), slot_(slot),
        RendererID_(0), LocalBuffer_(nullptr),
        Width_(0), Height_(0), BPP_(0)
{
    
    stbi_set_flip_vertically_on_load(1);
    
    LocalBuffer_ = stbi_load(filepath.c_str(), &Width_, &Height_, &BPP_, 4);

    GL_CALL(glGenTextures(1, &RendererID_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, RendererID_));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width_, Height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    if(LocalBuffer_)
    { 
        stbi_image_free(LocalBuffer_);
        Debugger<DEBUG_LEVEL>::Log_Console("Texture loaded successfully");
    }
    else
    {
        Debugger<DEBUG_LEVEL>::Log_Console("!!! Texture failed to load\n",
         Filepath_, " : ", 
         "(", Width_, " x ", Height_, ")");
	    Debugger<DEBUG_LEVEL>::Log_Console(stbi_failure_reason());
    }
}

Texture::~Texture()
{
    GL_CALL(glDeleteTextures(1, &RendererID_));
}

void Texture::Bind() const
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot_))
    GL_CALL(glBindTexture(GL_TEXTURE_2D, RendererID_));
}

void Texture::Unbind() const
{
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}


