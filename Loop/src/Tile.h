#pragma once

#include <raylib.h>

#include "DrawUtils.h"
#include "Sprite.h"

class Tile : public DrawItem
{
private:
    Sprite* sprite;
    Color color;

    enum class PortIndex
    {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
    };
    bool availablePorts[4];

public:
    explicit Tile(Sprite* sprite, Color color);

    Vector2 size() const override;

    void draw() const override;
};
