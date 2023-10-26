#include "SpriteLoader.h"

SpriteDescriptor SpriteDescriptor::of(const std::string& friendlyId)
{
    return SpriteDescriptor{friendlyId};
}

SpriteDescriptor::SpriteDescriptor(const std::string& friendlyId) :
        friendlyId(friendlyId)
{
}

SpriteDescriptor& SpriteDescriptor::add(SpriteVariant variant, const std::string& fileName)
{
    fileNamesByVariant.insert({variant, fileName});
    return *this;
}

std::string SpriteDescriptor::getId() const
{
    return friendlyId;
}

std::string SpriteDescriptor::getFileNameByVariant(SpriteVariant variant) const
{
    auto it = fileNamesByVariant.find(variant);
    if (it == fileNamesByVariant.end()) {
        return {};
    }
    return it->second;
}

void SpriteLoader::loadSprite(const SpriteDescriptor& sd)
{
    std::string friendlyId = sd.getId();
    auto it = sprites.find(friendlyId);
    if (it == sprites.end()) {
        sd.getFileNameByVariant(SpriteVariant::PLAIN);
        sd.getFileNameByVariant(SpriteVariant::OUTLINE);
        //TODO
        Texture2D texture = LoadTexture(fileName.c_str());
        sprites.insert({friendlyId, new Sprite(texture)});
    }
}

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
