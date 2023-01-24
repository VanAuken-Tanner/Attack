#include "TextureManager.h"

TextureManager::TextureManager()
{
    AddTexture(new Texture(bg_path_,TEXTURE_LAYER::BACKGROUND), TEXTURE_LAYER::BACKGROUND);
    AddTexture(new Texture(enemy_path_,TEXTURE_LAYER::ENEMY), TEXTURE_LAYER::ENEMY);
    AddTexture(new Texture(projectile_path_,TEXTURE_LAYER::MISSLE), TEXTURE_LAYER::MISSLE);
    AddTexture(new Texture(player_path_,TEXTURE_LAYER::PLAYER), TEXTURE_LAYER::PLAYER);
    AddTexture(new Texture(banner_path_,TEXTURE_LAYER::MENU), TEXTURE_LAYER::MENU);
    AddTexture(new Texture(font_path_,TEXTURE_LAYER::TEXT), TEXTURE_LAYER::TEXT);
}