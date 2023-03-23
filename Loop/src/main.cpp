#include <raylib.h>

int main()
{
    InitWindow(600, 800, "Loop");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawLine(100, 100, 200, 200, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
