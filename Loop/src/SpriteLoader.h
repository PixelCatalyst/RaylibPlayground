#pragma once

#include <string>
#include <map>

#include "Sprite.h"

class SpriteLoader
{
private:
    std::map<std::string, Sprite*> sprites;
public:
    void loadSprite(const std::string& friendlyId, const std::string& fileName);

    Sprite* getSprite(const std::string& friendlyId) const;
};
