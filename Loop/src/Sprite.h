#pragma once

#include <raylib.h>

#include <string>

class Sprite
{
private:
    Texture2D texture;
public:
    explicit Sprite(const Texture2D& texture);

    void draw(Color color) const;
};
