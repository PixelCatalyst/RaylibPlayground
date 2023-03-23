#include <raylib.h>
#include <rlgl.h>

struct Triangle
{
    const Vector2 a;
    const Vector2 b;
    const Vector2 c;
    const Color color;

    Triangle(const Vector2& a, const Vector2& b, const Vector2& c, const Color& color) :
            a(a), b(b), c(c), color(color)
    {
    }
};

struct GameState
{
    float angle = 0.0f;
};

void update(GameState& gameState)
{
    const float degreesPerSecond = 180.0f;
    float deltaSeconds = GetFrameTime();
    gameState.angle += degreesPerSecond * deltaSeconds;
    if (gameState.angle >= 360.0f) {
        gameState.angle = gameState.angle - 360.0f;
    }
}

void draw(const GameState& gameState, const Triangle& triangle)
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

int main()
{
    InitWindow(600, 800, "Loop");
    SetTargetFPS(60);

    Triangle triangle(
            Vector2{-50, 50},
            Vector2{50, 50},
            Vector2{0, -50},
            SKYBLUE);

    GameState gameState;
    while (!WindowShouldClose()) {
        update(gameState);
        draw(gameState, triangle);
    }

    CloseWindow();

    return 0;
}
