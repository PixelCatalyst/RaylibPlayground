#pragma once

#include <raylib.h>

#include "DrawItem.h"
#include "Port.h"
#include "Sprite.h"

class Tile : public DrawItem
{
private:
    PortSet portSet;
    Sprite* sprite;
    Color color;
    int rotation;
public:
    explicit Tile(PortSet portSet, Sprite* sprite, Color color, int rotation);

    static float size();

    void draw() const override;

    void rotate();
};
