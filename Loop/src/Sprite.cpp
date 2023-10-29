#include <raylib.h>

#include "Sprite.h"

Sprite::Sprite(const Texture2D& texture, const Texture2D& outlineTexture) :
        texture{texture},
        outlineTexture{outlineTexture}
{
}

void Sprite::draw(Color color, SpriteVariant variant) const
{
    if (variant == SpriteVariant::PLAIN) {
        DrawTexture(texture, 0, 0, color);
    } else if (variant == SpriteVariant::OUTLINE) {
        DrawTexture(outlineTexture, 0, 0, color);
    }
}
