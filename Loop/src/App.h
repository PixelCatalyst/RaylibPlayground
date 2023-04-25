#pragma once

#include <raylib.h>
#include <rlgl.h>

#include "Mosaic.h"
#include "SpriteLoader.h"
#include "TileDefinition.h"
#include "TileFactory.h"

struct GameState
{
    float angle{0.0f};
};

class App
{
private:
    GameState gameState;

    SpriteLoader* spriteLoader;
    TileDefinition* tileDefinition;
    TileFactory* tileFactory;
    Mosaic* mosaic;
public:
    explicit App();

    void init();

    bool isRunning();

    void update();

    void draw();

    void shutdown();
};
