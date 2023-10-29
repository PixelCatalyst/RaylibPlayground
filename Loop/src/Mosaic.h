#pragma once

#include <map>
#include <set>

#include "DrawItem.h"
#include "TileFactory.h"
#include "Tile.h"
#include "Sprite.h"

using Coord = std::pair<unsigned, unsigned>;

class Mosaic
{
private:
    std::map<Coord, Tile> tiles;
    std::set<Coord> tilesToUpdate;
    const unsigned width;
    const unsigned height;

    void drawTiles() const;

    void drawTilesOutline() const;

public:
    Mosaic(const TileFactory& tileFactory, unsigned width, unsigned height);

    void update(float deltaSeconds);

    void onLeftClick(const Vector2& mousePos, const Vector2& viewportSize);

    void drawCentered(const Vector2& viewportSize) const;

    void drawCenteredAsOutline(const Vector2& viewportSize) const;

    void rotateTile(unsigned x, unsigned y);
};
