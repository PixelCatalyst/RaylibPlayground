#pragma once

#include "Tile.h"
#include "SpriteLoader.h"

#include <map>

class TileDefinition
{
private:
    SpriteLoader& spriteLoader;

    using SpriteIdWithRotation = std::pair<std::string, int>;
    std::map<PortSet, SpriteIdWithRotation> portsToSprite;
    const char* basePath = "assets/tiles/";
    char* currentDefFileText = nullptr;

    std::istringstream loadDefFileText();

    void parseLine(const std::string& line);

    void unloadDefFileText();

public:
    explicit TileDefinition(SpriteLoader& spriteLoader);

    void initFromFile();

    std::pair<std::string, int> getSpriteForGivenPortSet(PortSet portSet) const;
};
