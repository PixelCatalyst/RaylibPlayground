#pragma once

#include "Tile.h"
#include "SpriteLoader.h"

#include <map>
#include <vector>

class TileDefinition
{
private:
    using SpriteIdWithRotation = std::pair<std::string, int>;
    std::map<PortSet, SpriteIdWithRotation> portsToSprite;
public:
    void populateTile(PortSet portSet, const std::string& friendlyId);

    std::pair<std::string, int> findByPortSet(PortSet portSet) const;
};

class TileDefinitionLoader
{
private:
    struct Context
    {
        const std::string defFilePath = "assets/tiles/tiledef";
        const std::string tilesBasePath = "assets/tiles/";
        const std::string outlineSpriteTag = "_outline";
        const std::string animGradientSpriteTag = "_gradient";

        TileDefinition tileDef;
        char* currentDefFileText = nullptr;
        std::string line;
        std::string token;
    };

    explicit TileDefinitionLoader() = default;

    static std::istringstream loadDefFileText(Context& context);

    static void parseLine(Context& context, SpriteLoader& spriteLoader);

    static void unloadDefFileText(Context& context);

public:
    static TileDefinition loadFromFile(SpriteLoader& spriteLoader);
};
