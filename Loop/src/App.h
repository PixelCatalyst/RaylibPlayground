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
    // TODO consider extracting coloring functionality
    constexpr static const int backgroundColor[3] = {103, 90, 131};
    constexpr static const int foregroundColor[3] = {176, 197, 229};

    GameState gameState;
    RenderTexture2D target;
    Shader coloringShader;

    SpriteLoader* spriteLoader{nullptr};
    TileFactory* tileFactory{nullptr};
    Mosaic* mosaic{nullptr};
public:
    explicit App();

    void init();

    bool isRunning();

    void update();

    void draw();

    void shutdown();
};
