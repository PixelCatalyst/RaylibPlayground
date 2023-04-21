#include <raylib.h>

#include "Sprite.h"

Sprite::Sprite(const std::string& fileName)
{
    texture = LoadTexture(fileName.c_str());
}

void Sprite::draw(Color color) const
{
    DrawTexture(texture, 0, 0, color);
}
