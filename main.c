#include <raylib.h>

#include "animation.h"
#include "inputhandle.h"
#include "player.h"

int main(void) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();
    Texture2D scarfy = LoadTexture("../Assets/scarfy.png");        // Texture loading
    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    initAnimationSprites();
    AnimatedSprite* sprite = generateAnimatedSprite(&scarfy, &frameRec, &position, 6, 20);
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


