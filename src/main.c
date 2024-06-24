#include <raylib.h>

#include "animation.h"
#include "inputhandle.h"
#include "physics.h"
#include "player.h"

int main(void) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();
    Texture2D scarfy = LoadTexture("../Assets/scarfy.png");        // Texture loading
    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    initAnimationSprites();
    const PhysicsObject* o = generatePhysicsObject(&position, 5.0f);
    AnimatedSprite* sprite = generateAnimatedSprite(&scarfy, &frameRec, &position, 6, 20);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        // handleInput();
        updatePhysics();

        BeginDrawing();
        animateSprite();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    destroyAnimatedSprite(sprite);
    unregisterPhysicsObject(o);
    return 0;
}


