#include <raylib.h>
#include <rlgl.h>

#include "Tile.h"

Tile::Tile(Sprite* sprite, Color color) :
        sprite{sprite},
        color{color}
{
    availablePorts[0] = availablePorts[1] = availablePorts[2] = availablePorts[3] = true;
}

float Tile::size()
{
    return 80.0f;
}

void Tile::draw() const
{
    sprite->draw(color);
}
