#pragma once

#include <string>
#include <map>

#include "Sprite.h"

// TODO Consider using spriteId value objects
// TODO Consider using default (error) sprite in case of missing asset
class SpriteLoader
{
private:
    std::map<std::string, Sprite*> sprites;
public:
    void loadSprite(const std::string& friendlyId, const std::string& fileName);

    Sprite* getSprite(const std::string& friendlyId) const;
};
