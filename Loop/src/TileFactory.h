#pragma once

#include "TileDefinitionLoader.h"
#include "Tile.h"

class TileFactory
{
private:
    SpriteLoader& spriteLoader;

    TileDefinition tileDef;
public:
    explicit TileFactory(SpriteLoader& spriteLoader);

    void initResources();

    Tile create(PortSet portSet) const;
};
