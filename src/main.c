#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>

#include "animation.h"
#include "inputhandle.h"
#include "utils/debugutils.h"
#include "physics.h"
#include "entity/magic.h"
#include "entity/player.h"
#include "tmx.h"
// #include "map.h"

#define TUTORIAL_PATH "../Assets/levels/tutorial_level.tmx"


Texture2D *LoadMapTexture(const char *fileName);

void UnloadMapTexture(Texture2D *tex);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
void drawInputEffect();
void drawPlayerStat();

// Frame buffer into which the map is rendered
RenderTexture2D mapFrameBuffer;

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

int a = 0;

void collideTest(struct _physicsObject* o) {
    printf("collide count: %d\n", ++a);
}

int main(int argc, char *argv[]) {
    SetTargetFPS(60);
    InitWindow(1920/2, 1080/2, "푸른별");
    InitAudioDevice();
    initAnimationSprites();
    initPhysics();
    initMagics();

    Texture2D texture = LoadTexture("../Assets/scarfy.png");

    initPlayer(&texture);
    // tmx_map* map = NULL;
    // initMap(argc, argv, &map);

    // if(map == NULL){ //eRRoR
    //     CloseWindow();
    //     return -1;
    // }

    Camera2D camera = { 0 };
    camera.target = *getPlayerPhysicsObject()->pos;
    camera.offset = (Vector2){ 1920/2/2.0f, 1080/2/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    RenderTmxMapToFramebuf(TUTORIAL_PATH, &mapFrameBuffer);
  
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        // loadMap(map, SCREENWIDTH, SCREENHEIGHT);
        tickPlayer();
        handleInput();
        updatePhysics(&delta);
        camera.target = *getPlayerPhysicsObject()->pos;
        BeginDrawing();
            BeginMode2D(camera);
                DrawTextureRec(
                    mapFrameBuffer.texture,
                    (Rectangle){0, 0, mapFrameBuffer.texture.width, -mapFrameBuffer.texture.height},
                    (Vector2){0.0, 0.0},
                    WHITE);
                animateSprite();
                drawMagic();
                drawPhysicsRect(getPlayerPhysicsObject(), RED);
                DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
                ClearBackground(RAYWHITE);
            EndMode2D();
            drawInputEffect();
            drawPlayerStat();
        EndDrawing();
    }
    destroyPlayer();
    destroyAnimatedSprites();
    destroyPhysicsObjects();
    destroyMagics();
    UnloadRenderTexture(mapFrameBuffer);
    // unLoadMap(map);
    CloseWindow();
    return 0;
}


void drawInputEffect() {
    if(!isInputBuffEmpty()) {
        DrawText(getInputBuff(), 190, 200, 20, BLACK);
    }
}

void drawPlayerStat() {
    DrawText(TextFormat("Health: %d, Mana: %d", getPlayerHealth(), getPlayerMana()), 0, 0, 20, BLACK);
    DrawText(TextFormat("X: %f, Y: %f", getPlayerPhysicsObject()->pos->x, getPlayerPhysicsObject()->pos->y), 0, 20, 20, BLACK);
}