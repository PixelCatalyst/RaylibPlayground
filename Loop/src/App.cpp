#include "App.h"

#include "DrawItem.h"

App::App() = default;

void App::init()
{
    InitWindow(700, 700, "Loop");
    SetTargetFPS(60);

    target = LoadRenderTexture(700, 700);
    coloringShader.init();
    colorPalette = ColorPalette::createProcedurally();
    coloringShader.setColors(colorPalette.getBackground(), colorPalette.getForeground());

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
        coloringShader.setColors(colorPalette.getBackground(), colorPalette.getForeground());
    }
}

void App::draw()
{
    BeginTextureMode(target);
    ClearBackground(BLACK);

    const Vector2 renderSize{
            static_cast<float>(GetRenderWidth()),
            static_cast<float>(GetRenderHeight())
    };
    mosaic->drawCentered(renderSize);

    EndTextureMode();

    BeginDrawing();

    coloringShader.enable();
    Rectangle sourceRect{0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height};
    Vector2 position{0.0f, 0.0f};
    DrawTextureRec(target.texture, sourceRect, position, WHITE);
    coloringShader.disable();

    EndDrawing();
}

void App::shutdown()
{
    CloseWindow();

    delete spriteLoader;
    delete tileFactory;
    delete mosaic;
}
