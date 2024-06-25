#include <raylib.h>
#include <stdio.h>

#include "animation.h"
#include "inputhandle.h"
#include "utils/debugutils.h"
#include "physics.h"
#include "player.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

int a =0 ;

void collideTest(struct _physicsObject* o) {
    printf("collide count: %d\n", ++a);
}

int main(int argc, char *argv[]) {
    SetTargetFPS(60);
    InitWindow(1920/2, 1080/2, "푸른별");
    InitAudioDevice();
    initAnimationSprites();
    initPhysics();

    initPlayer(LoadTexture("../Assets/scarfy.png"));
    // tmx_map* map = NULL;
    // initMap(argc, argv, &map);

    // if(map == NULL){ //eRRoR
    //     CloseWindow();
    //     return -1;
    // }
  
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        // loadMap(map, SCREENWIDTH, SCREENHEIGHT);
        handleInput();
        updatePhysics(&delta);

        BeginDrawing();
        animateSprite();
        drawPhysicsRect(getPlayerPhysicsObject(), RED);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    destroyPlayer();
    destroyAnimatedSprites();
    destroyPhysicsObjects();
    // unLoadMap(map);
    CloseWindow();
    return 0;
}


