#include "App.h"

#include "DrawItem.h"

App::App() = default;

void App::init()
{
    InitWindow(700, 700, "Loop");
    SetTargetFPS(60);

    spriteLoader = new SpriteLoader();
    tileFactory = new TileFactory(*spriteLoader);
    tileFactory->initResources();
    mosaic = new Mosaic(*tileFactory, 8, 8);
}

bool App::isRunning()
{
    return !WindowShouldClose();
}

void App::update()
{
    const float degreesPerSecond = 180.0f;
    float deltaSeconds = GetFrameTime();
    gameState.angle += degreesPerSecond * deltaSeconds;
    if (gameState.angle >= 360.0f) {
        gameState.angle = gameState.angle - 360.0f;
    }
}

void App::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    const Vector2 renderSize{
            static_cast<float>(GetRenderWidth()),
            static_cast<float>(GetRenderHeight())
    };
    mosaic->drawCentered(renderSize);

    EndDrawing();
}

void App::shutdown()
{
    CloseWindow();

    delete spriteLoader;
    delete tileFactory;
    delete mosaic;
}
