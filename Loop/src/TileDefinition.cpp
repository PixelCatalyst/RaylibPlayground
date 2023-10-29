#include "TileDefinition.h"

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
    context.currentDefFileText = LoadFileText(context.defFilePath.c_str());
    return std::istringstream{context.currentDefFileText};
}

void TileDefinitionLoader::parseLine(Context& context, SpriteLoader& spriteLoader)
{
    std::istringstream lineStream{context.line};
    lineStream >> context.token;
    size_t dotPos = context.token.find_last_of('.');
    std::string friendlyId = context.token.substr(0, dotPos);
    std::string fileExtension = context.token.substr(dotPos);

    if (spriteLoader.getSprite(friendlyId) != nullptr) {
        TraceLog(LOG_WARNING, "Detected definition of already used tile sprite, can produce unexpected results");
    }
    spriteLoader.loadSprite(
            SpriteDescriptor::of(friendlyId)
                    .add(SpriteVariant::PLAIN,
                         context.tilesBasePath + friendlyId + fileExtension)
                    .add(SpriteVariant::OUTLINE,
                         context.tilesBasePath + friendlyId + context.outlineSpriteTag + fileExtension)
    );
    if (spriteLoader.getSprite(friendlyId) == nullptr) {
        TraceLog(LOG_FATAL, "Unable to parse tile definition because given sprite was not loaded");
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
        TraceLog(LOG_FATAL, "Unable to find sprite for given tile port set, tile definition seems incomplete");
    }
    return it->second;
}
