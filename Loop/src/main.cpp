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

int main()
{
    InitWindow(600, 800, "Loop");

    Triangle triangle(
            Vector2{-50, 50},
            Vector2{50, 50},
            Vector2{0, -50},
            SKYBLUE);
    float angle = 0.0f;

    while (!WindowShouldClose()) {
        angle += 0.1f;
        if (angle >= 360.0f) {
            angle = angle - 360.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlPushMatrix();
        {
            rlTranslatef(300.0f, 400.0f, 0.0f);
            rlRotatef(angle, 0.0f, 0.0f, 1.0f);
            DrawTriangle(triangle.a, triangle.b, triangle.c, triangle.color);
        }
        rlPopMatrix();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
