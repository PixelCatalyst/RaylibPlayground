#pragma once

#include <raylib.h>

#include <string>

enum class SpriteVariant {
    PLAIN,
    OUTLINE
};

class Sprite
{
private:
    Texture2D texture;
    Texture2D outlineTexture;
public:
    explicit Sprite(const Texture2D& texture, const Texture2D& outlineTexture);

    void draw(Color color, SpriteVariant variant) const;
};
