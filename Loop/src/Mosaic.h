#pragma once

#include <map>

#include "DrawItem.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Sprite.h"

using Coord = std::pair<unsigned, unsigned>;

class Mosaic
{
private:
    std::map<Coord, Tile> tiles;
    const unsigned width;
    const unsigned height;

    void drawTiles() const;

public:
    Mosaic(const TileFactory& tileFactory, unsigned width, unsigned height);

    void drawCentered(const Vector2& viewportSize) const;
};
