#pragma once

#include "Debug.h"

#include "Layer.h"
#include "engine\Texture.h"

#define BANNER_LAYER        0
#define TEXT_LAYER          1

//TODO 
//      constructor should make new
//      Writing text should ref objects
//
//      Destructor cleanup

class Banner
{
public:
    Banner();
    ~Banner() {}

    inline void BindTextures() { BannerTexture_->Bind(); TextTexture_->Bind(); }

    void WriteText(std::string& msg);
    void UpdateBufferData(std::vector<float>& vertices, std::vector<unsigned int>& inidces, int& InidcePos);

private:
    glm::vec2 GetTextureCoords(char val);
    const glm::vec2 text_coord_offset_ = {16.0f, 0.0f};
    const glm::vec3 text_pos_root_ = {-7.0f, -3.0f, 0.0f};
    const glm::vec3 text_pos_offset_ = {0.15f, 0.0f, 0.0f};

    std::string banner_path_ = "res/art/blue_square_25a.png";
    std::string font_path_ = "res/art/abz_font.png";
    Layer Banner_;
    Layer Text_;

    Texture* BannerTexture_;
    Texture* TextTexture_;
    
    const int texture_slot_count_ = 2;
    int texture_slots_[2] = {0, 1};
};