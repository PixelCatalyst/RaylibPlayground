#include <raylib.h>

int main()
{
    InitWindow(800, 450, "RaylibPlayground | HelloWorld");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello RaylibPlayground!", 190, 200, 36, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
