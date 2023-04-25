#include <raylib.h>
#include <rlgl.h>

#include "Tile.h"

Tile::Tile(Sprite* sprite, Color color) :
        sprite{sprite},
        color{color}
{
}

float Tile::size()
{
    return 80.0f;
}

void Tile::draw() const
{
    sprite->draw(color);
}
