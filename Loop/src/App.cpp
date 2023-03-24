#include "App.h"

App::App() :
        triangle{Vector2{-50, 50},
                 Vector2{50, 50},
                 Vector2{0, -50},
                 SKYBLUE}
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

    rlPushMatrix();
    {
        rlTranslatef(300.0f, 400.0f, 0.0f);
        rlRotatef(gameState.angle, 0.0f, 0.0f, 1.0f);
        DrawTriangle(triangle.a, triangle.b, triangle.c, triangle.color);
    }
    rlPopMatrix();

    EndDrawing();
}

void App::close()
{
    CloseWindow();
}
