#include <raylib.h>

#include "animation.h"
#include "inputhandle.h"
#include "player.h"

typedef enum _state {

} State;

int main(void) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        // handleInput();

        BeginDrawing();
        animateSprite();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    destroyAnimatedSprite(sprite);
    return 0;
}


