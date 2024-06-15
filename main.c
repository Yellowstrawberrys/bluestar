#include <raylib.h>
#include <string.h>

typedef enum _state {

} State;

int main(void) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    return 0;
}
