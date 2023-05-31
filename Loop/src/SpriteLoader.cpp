#include "SpriteLoader.h"

void SpriteLoader::loadSprite(const std::string& friendlyId, const std::string& fileName)
{
    auto it = sprites.find(friendlyId);
    if (it == sprites.end()) {
        Texture2D texture = LoadTexture(fileName.c_str());
        sprites.insert({friendlyId, new Sprite(texture)});
    }
}

Sprite* SpriteLoader::getSprite(const std::string& friendlyId) const
{
    auto it = sprites.find(friendlyId);
    if (it == sprites.end()) {
        return nullptr;
    }
    return it->second;
}
