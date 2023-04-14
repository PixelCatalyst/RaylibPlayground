#pragma once

#include <raylib.h>

#include <string>

class Sprite
{
private:
    Texture2D texture;
public:
    explicit Sprite(const std::string& fileName);

    void draw(Color color) const;
};
