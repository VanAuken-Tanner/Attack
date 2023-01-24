#pragma once

#include <vector>

#include "Texture.h"

class TextureData
{
public:
    TextureData(unsigned int slot, Texture* texture) : slot_(slot), texture_(texture) {}
    unsigned int slot_;
    Texture* texture_;
};

class TextureManager
{
public:
    TextureManager();
    ~TextureManager() {};
    inline const int GetNumTextureSlots() { return NUM_LAYERS; }
    inline int* GetTextureSlots() { return &textures[0]; }
    inline void BindTextures() {for (TextureData* texture_data : Textures_) texture_data->texture_->Bind(); }
    inline void AddTexture(Texture* texture, TEXTURE_LAYER layer) { Textures_.push_back(new TextureData(layer,texture)); }

private:
    const unsigned int texture_slots_ = NUM_LAYERS;
    int textures[NUM_LAYERS] = {
        BACKGROUND,
        ENEMY,
        MISSLE,
        PLAYER,
        MENU,
        TEXT
    };

    std::vector<TextureData*> Textures_;

    std::string bg_path_ = "res/art/Mountains.png";
    std::string enemy_path_ = "res/art/goblin.png";
    std::string projectile_path_ = "res/art/blue_square_25a.png";
    std::string player_path_ = "res/art/Wizard.png";
    std::string banner_path_ = "res/art/solo_ui_bar.png";
    std::string font_path_ = "res/art/abz_font.png";
};