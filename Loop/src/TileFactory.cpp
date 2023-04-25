#include "TileFactory.h"

TileFactory::TileFactory(const TileDefinition& tileDefinition, SpriteLoader& spriteLoader) :
        tileDefinition{tileDefinition},
        spriteLoader{spriteLoader}
{
}

Tile TileFactory::create(PortSet portSet) const
{
    auto [spriteId, rotation] = tileDefinition.getSpriteForGivenPortSet(portSet);
    return Tile(spriteLoader.getSprite(spriteId), BEIGE);
}
