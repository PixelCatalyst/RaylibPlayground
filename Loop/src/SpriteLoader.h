#pragma once

#include <string>
#include <map>

#include "Sprite.h"

// TODO Consider using spriteId value objects
// TODO Consider using default (error) sprite in case of missing asset

class SpriteDescriptor
{
private:
    const std::string friendlyId;
    std::map<SpriteVariant, std::string> fileNamesByVariant;

    explicit SpriteDescriptor(const std::string& friendlyId);

public:
    static SpriteDescriptor of(const std::string& friendlyId);

    SpriteDescriptor& add(SpriteVariant variant, const std::string& fileName);

    std::string getId() const;

    std::string getFileNameByVariant(SpriteVariant variant) const;
};

class SpriteLoader
{
private:
    std::map<std::string, Sprite*> sprites;

    Texture2D loadTexture(const std::string& fileName);
public:
    void loadSprite(const SpriteDescriptor& sd);

    Sprite* getSprite(const std::string& friendlyId) const;
};
