#pragma once

#include <raylib.h>

#include <string>

enum class SpriteVariant
{
    PLAIN,
    OUTLINE,
    ANIM_GRADIENT
};

class Sprite
{
private:
    Texture2D texture;
    Texture2D outlineTexture;
    Texture2D animGradientTexture;
public:
    explicit Sprite(const Texture2D& texture, const Texture2D& outlineTexture, const Texture2D& animGradientTexture);

    void draw(Color color, SpriteVariant variant) const;
};
