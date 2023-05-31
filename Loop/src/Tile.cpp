#include <raylib.h>
#include <rlgl.h>

#include "Tile.h"

Tile::Tile(PortSet portSet, Sprite* sprite, Color color, int rotation) :
        portSet{portSet},
        sprite{sprite},
        color{color},
        rotation{rotation}
{
}

float Tile::size()
{
    return 80.0f;
}

void Tile::draw() const
{
    float halfSize = Tile::size() / 2.0f;
    rlPushMatrix();
    rlTranslatef(halfSize, halfSize, 0);
    rlRotatef(90.0f * rotation, 0, 0, 1);
    rlTranslatef(-halfSize, -halfSize, 0);
    sprite->draw(color);
    rlPopMatrix();
}

void Tile::rotate()
{
    portSet.rotate();
    rotation = (rotation + 1) % 4;
}
