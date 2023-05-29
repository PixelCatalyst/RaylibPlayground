#include "TileDefinitionLoader.h"

#include <raylib.h>

#include <sstream>

TileDefinition TileDefinitionLoader::loadFromFile(SpriteLoader& spriteLoader)
{
    Context context;
    std::istringstream tileDefStream = loadDefFileText(context);
    while (std::getline(tileDefStream, context.line)) {
        if (!context.line.empty()) {
            parseLine(context, spriteLoader);
        }
    }
    unloadDefFileText(context);
    return context.tileDef;
}

std::istringstream TileDefinitionLoader::loadDefFileText(Context& context)
{
    context.currentDefFileText = LoadFileText(context.defFilePath);
    return std::istringstream{context.currentDefFileText};
}

void TileDefinitionLoader::parseLine(Context& context, SpriteLoader& spriteLoader)
{
    std::istringstream lineStream{context.line};
    lineStream >> context.token;
    size_t dotPos = context.token.find_last_of('.');
    std::string friendlyId = context.token.substr(0, dotPos);
    if (spriteLoader.getSprite(friendlyId) != nullptr) {
        //TODO warning, tile redefinition
    }
    spriteLoader.loadSprite(friendlyId, context.tilesBasePath + context.token);
    if (spriteLoader.getSprite(friendlyId) == nullptr) {
        //TODO fatal error, could not load sprite
    }
    PortSet portSet;
    while (lineStream >> context.token) {
        Port port = Port::fromString(context.token);
        if (port.isInvalid()) {
            TraceLog(LOG_WARNING, "Malformed port in tile definition");
        } else {
            portSet.add(port);
        }
    }
    context.tileDef.populateTile(portSet, friendlyId);
}

void TileDefinitionLoader::unloadDefFileText(Context& context)
{
    UnloadFileText(context.currentDefFileText);
    context.currentDefFileText = nullptr;
}

void TileDefinition::populateTile(PortSet portSet, const std::string& friendlyId)
{
    for (int i = 0; i < 4; ++i) {
        portsToSprite.insert({portSet, std::make_pair(friendlyId, i)});
        portSet.rotate();
    }
}

std::pair<std::string, int> TileDefinition::findByPortSet(PortSet portSet) const
{
    auto it = portsToSprite.find(portSet);
    if (it == portsToSprite.end()) {
        //TODO handle missing sprite error (should never happen in nominal conditions but should be handled anyway)
        TraceLog(LOG_ERROR, "No sprite for given port set");
    }
    return it->second;
}
