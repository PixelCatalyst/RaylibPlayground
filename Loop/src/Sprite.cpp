#include <raylib.h>

#include "Sprite.h"

Sprite::Sprite(const Texture2D& texture) :
        texture{texture}
{
}

void Sprite::draw(Color color) const
{
    DrawTexture(texture, 0, 0, color);
}
