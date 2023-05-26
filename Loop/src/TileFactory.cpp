#include "TileFactory.h"

TileFactory::TileFactory(SpriteLoader& spriteLoader) :
        spriteLoader{spriteLoader}
{
}

void TileFactory::initResources()
{
    tileDef = TileDefinitionLoader::loadFromFile(spriteLoader);
}

Tile TileFactory::create(PortSet portSet) const
{
    auto [spriteId, rotation] = tileDef.findByPortSet(portSet);
    return Tile(spriteLoader.getSprite(spriteId), BEIGE);
}
