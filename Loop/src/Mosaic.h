#pragma once

#include <map>

#include "DrawItem.h"
#include "Tile.h"
#include "Sprite.h"

using Coord = std::pair<unsigned, unsigned>;

class Mosaic
{
private:
    std::map<Coord, Tile> tiles;
    const unsigned width;
    const unsigned height;

    Sprite* tile1Sprite;
    Sprite* tile2aSprite;
    Sprite* tile2bSprite;
    Sprite* tile3Sprite;
    Sprite* tile4Sprite;

    void drawTiles() const;

public:
    Mosaic(unsigned width, unsigned height);

    ~Mosaic();

    void drawCentered(const Vector2& viewportSize) const;
};
