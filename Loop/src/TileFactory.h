#pragma once

#include "TileDefinition.h"
#include "Tile.h"

class TileFactory
{
private:
    const TileDefinition& tileDefinition;
    SpriteLoader& spriteLoader;
public:
    explicit TileFactory(const TileDefinition& tileDefinition, SpriteLoader& spriteLoader);

    Tile create(PortSet portSet) const;
};
