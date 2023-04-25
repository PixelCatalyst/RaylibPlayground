#include "TileDefinition.h"

#include <raylib.h>

#include <sstream>

TileDefinition::TileDefinition(SpriteLoader& spriteLoader) :
        spriteLoader{spriteLoader}
{
}

void TileDefinition::initFromFile()
{
    std::istringstream tileDefStream = loadDefFileText();
    std::string line;
    while (std::getline(tileDefStream, line)) {
        if (!line.empty()) {
            parseLine(line);
        }
    }
    unloadDefFileText();
}

std::istringstream TileDefinition::loadDefFileText()
{
    currentDefFileText = LoadFileText("assets/tiles/tiledef");
    return std::istringstream{currentDefFileText};
}

void TileDefinition::parseLine(const std::string& line)
{
    std::istringstream lineStream{line};
    std::string token;
    lineStream >> token;
    size_t pos = token.find_last_of('.');
    std::string friendlyId = token.substr(0, pos);
    if (spriteLoader.getSprite(friendlyId) != nullptr) {
        //TODO warning, tile redefinition
    }
    spriteLoader.loadSprite(friendlyId, basePath + token);
    if (spriteLoader.getSprite(friendlyId) == nullptr) {
        //TODO fatal error, could not load sprite
    }
    PortSet portSet;
    while (lineStream >> token) {
        Port port = Port::fromString(token);
        if (port.isInvalid()) {
            TraceLog(LOG_WARNING, "Malformed port in tile definition");
        } else {
            portSet.add(port);
        }
    }
    portsToSprite.insert({portSet, std::make_pair(friendlyId, 0)});
}

void TileDefinition::unloadDefFileText()
{
    UnloadFileText(currentDefFileText);
}

std::pair<std::string, int>TileDefinition::getSpriteForGivenPortSet(PortSet portSet) const
{
    auto it = portsToSprite.find(portSet);
    if (it == portsToSprite.end()) {
        //TODO handle missing sprite error (should never happen in nominal conditions but should be handled anyway)
        TraceLog(LOG_ERROR, "No sprite for given port set");
    }
    return it->second;
}
