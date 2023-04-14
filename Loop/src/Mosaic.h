#pragma once

#include <map>

#include "DrawUtils.h"
#include "Tile.h"
#include "Sprite.h"

using Coord = std::pair<unsigned, unsigned>;

class Mosaic : public DrawItem
{
private:
    std::map<Coord, Tile> tiles;
    unsigned width;
    unsigned height;

    Sprite* tile1Sprite;
    Sprite* tile2aSprite;
    Sprite* tile2bSprite;
    Sprite* tile3Sprite;
    Sprite* tile4Sprite;
public:
    Mosaic(unsigned width, unsigned height);

    ~Mosaic() override;

    Vector2 size() const override;

    void draw() const override;
};
