#include <raylib.h>

#include "animation.h"
#include "inputhandle.h"
#include "player.h"
#include "map.h"
#include "tmx_/raytmx.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

int main(int argc, char *argv[]) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();
    Texture2D scarfy = LoadTexture("../Assets/scarfy.png");        // Texture loading
    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    initAnimationSprites();
    AnimatedSprite* sprite = generateAnimatedSprite(&scarfy, &frameRec, &position, 6, 20);

    // initMap(argc, argv, &map);
    tmx_map* map = NULL;
    initMap(argc, argv, &map);

    if(map == NULL){ //eRRoR
        CloseWindow();
        return -1;
    }
  
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        loadMap(map, SCREENWIDTH, SCREENHEIGHT);
        // handleInput();

        BeginDrawing();
        animateSprite();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    destroyAnimatedSprite(sprite);
    unLoadMap(map);
    CloseWindow();
    return 0;
}


