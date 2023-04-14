#include "Tile.h"

Tile::Tile(Sprite* sprite, Color color) :
        sprite{sprite},
        color{color}
{
    availablePorts[0] = availablePorts[1] = availablePorts[2] = availablePorts[3] = true;
}

Vector2 Tile::size() const
{
    return Vector2{80.0f, 80.0f};
}

void Tile::draw() const
{
    sprite->draw(color);
}
