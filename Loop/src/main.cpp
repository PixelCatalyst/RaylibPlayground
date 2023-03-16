#include <raylib.h>

int main()
{
    InitWindow(600, 800, "Loop");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
