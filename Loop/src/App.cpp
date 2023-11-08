#include "App.h"

#include "DrawItem.h"

#include <ctime>

App::App() = default;

void App::init()
{
    InitWindow(700, 700, "Loop");
    SetTargetFPS(60);

    unsigned seed = std::time(nullptr);
    seed = seed ^ ((seed & 0x00FF) << 13);
    SetRandomSeed(seed);

    target = LoadRenderTexture(700, 700);
    secondaryTarget = LoadRenderTexture(700, 700);

    fadeShader = LoadShader(nullptr, "assets/shaders/radial_fade.frag");
    textureLoc = GetShaderLocation(fadeShader, "texture1");

    coloringShader.init();
    colorPalette = ColorPalette::createProcedurally();

    spriteLoader = new SpriteLoader();
    tileFactory = new TileFactory(*spriteLoader);
    tileFactory->initResources();
    mosaic = new Mosaic(*tileFactory, 8, 8);
}

bool App::isRunning()
{
    return !WindowShouldClose();
}

bool outline = false;

void App::update()
{
    const float degreesPerSecond = 180.0f;
    float deltaSeconds = GetFrameTime();
    gameState.angle += degreesPerSecond * deltaSeconds;
    if (gameState.angle >= 360.0f) {
        gameState.angle = gameState.angle - 360.0f;
    }

    mosaic->update(deltaSeconds);

    const Vector2 renderSize{
            static_cast<float>(GetRenderWidth()),
            static_cast<float>(GetRenderHeight())
    };
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        mosaic->onLeftClick(mousePos, renderSize);
    }

    // TODO Temporary testing only; Change color palette on level change
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        colorPalette = ColorPalette::createProcedurally();
    }

    // TODO Temporary testing only; Change tile drawing mode to outline
    if (IsKeyPressed(KEY_ENTER)) {
        outline = !outline;
    }
}

void App::draw()
{
    const Vector2 renderSize{
            static_cast<float>(GetRenderWidth()),
            static_cast<float>(GetRenderHeight())
    };
    Rectangle sourceRect{
            0.0f,
            0.0f,
            static_cast<float>(target.texture.width),
            static_cast<float>(-target.texture.height)
    };
    Vector2 position{0.0f, 0.0f};

    BeginTextureMode(target);
    ClearBackground(BLACK);
    mosaic->drawCentered(renderSize);
    EndTextureMode();

    BeginTextureMode(secondaryTarget);
    ClearBackground(BLACK);
    mosaic->drawCenteredAsOutline(renderSize);
    EndTextureMode();

    BeginTextureMode(target);
    coloringShader.setColors(colorPalette.getBackground(), colorPalette.getForeground());
    coloringShader.enable();
    DrawTextureRec(target.texture, sourceRect, position, WHITE);
    coloringShader.disable();
    EndTextureMode();

    BeginTextureMode(secondaryTarget);
    coloringShader.setColors(colorPalette.getBackground(), colorPalette.getForeground());
    coloringShader.enable();
    DrawTextureRec(secondaryTarget.texture, sourceRect, position, WHITE);
    coloringShader.disable();
    EndTextureMode();

    BeginDrawing();
    BeginShaderMode(fadeShader);
    SetShaderValueTexture(fadeShader, textureLoc, secondaryTarget.texture);
    DrawTextureRec(target.texture, sourceRect, position, WHITE);
    EndShaderMode();
    EndDrawing();
}

void App::shutdown()
{
    CloseWindow();

    delete spriteLoader;
    delete tileFactory;
    delete mosaic;
}
