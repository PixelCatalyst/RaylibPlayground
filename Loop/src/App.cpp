#include "App.h"

#include "DrawUtils.h"

App::App() :
        mosaic(4, 4)
{
}

void App::init()
{
    InitWindow(600, 800, "Loop");
    SetTargetFPS(60);
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

    DrawUtils::drawCentered(mosaic);

    EndDrawing();
}

void App::close()
{
    CloseWindow();
}
