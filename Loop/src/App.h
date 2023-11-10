#pragma once

#include <raylib.h>
#include <rlgl.h>

#include "Mosaic.h"
#include "SpriteLoader.h"
#include "TileDefinition.h"
#include "TileFactory.h"
#include "RadialFadeShader.h"
#include "ColoringShader.h"
#include "ColorPalette.h"

enum class GamePhase : int8_t
{
    PLAY,
    END_TRANSITION,
    END
};

struct GameState
{
    GamePhase phase{GamePhase::PLAY};
};

class App
{
private:
    GameState gameState;
    ColorPalette colorPalette{};
    ColoringShader coloringShader;
    RadialFadeShader radialFadeShader;
    RenderTexture2D target{};
    RenderTexture2D secondaryTarget{};

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
