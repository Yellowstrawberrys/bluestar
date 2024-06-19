#include <raylib.h>
#include "inputhandle.h"

typedef enum _state {

} State;

int main(void) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();
    while (!WindowShouldClose()) {
        handleInput();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    return 0;
}


