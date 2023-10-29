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
        Texture2D texture = loadTexture(sd.getFileNameByVariant(SpriteVariant::PLAIN));
        Texture2D outlineTexture = loadTexture(sd.getFileNameByVariant(SpriteVariant::OUTLINE));
        sprites.insert({friendlyId, new Sprite(texture, outlineTexture)});
    }
}

Texture2D SpriteLoader::loadTexture(const std::string& fileName)
{
    Texture2D texture{};
    if (!fileName.empty()) {
        texture = LoadTexture(fileName.c_str());
    }
    return texture;
}

Sprite* SpriteLoader::getSprite(const std::string& friendlyId) const
{
    auto it = sprites.find(friendlyId);
    if (it == sprites.end()) {
        return nullptr;
    }
    return it->second;
}
