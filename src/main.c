#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>

#include "animation.h"
#include "inputhandle.h"
#include "maps/map.h"
#include "maps/MapCollision.h"
#include "maps/TmxCollisionMapper.h"
#include "utils/debugutils.h"
#include "physics.h"
#include "entity/magic.h"
#include "entity/player.h"
#include "tmx.h"

#define TUTORIAL_PATH "../Assets/levels/tutorial_level.tmx"

<<<<<<< Updated upstream
=======
#define SCREENWIDTH 1920/2
#define SCREENHEIGHT 1080/2
#define TILEWIDTH 32
#define TILEHEIGHT 32

void initDrawInputEffect();
>>>>>>> Stashed changes

Texture2D *LoadMapTexture(const char *fileName);

void UnloadMapTexture(Texture2D *tex);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
void drawInputEffect();
void drawPlayerStat(Player player);

// Frame buffer into which the map is rendered
RenderTexture2D mapFrameBuffer;

<<<<<<< Updated upstream
#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

=======
>>>>>>> Stashed changes
int a = 0;

void collideTest(struct _physicsObject* o) {
    printf("collide count: %d\n", ++a);
}

int main(int argc, char *argv[]) {
    SetTargetFPS(60);
<<<<<<< Updated upstream
    InitWindow(1920/2, 1080/2, "푸른별");
=======
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "푸른별");
    Player player;
>>>>>>> Stashed changes
    InitAudioDevice();
    initAnimationSprites();
    initPhysics();
    initMagics();
<<<<<<< Updated upstream
=======
    initDrawInputEffect();
    // initEnemy();
    //
    Texture2D texture = LoadTexture("../Assets/walk.png");
    tmx_resource_manager* rm = tmx_make_resource_manager();
>>>>>>> Stashed changes

    initPlayer(&texture, &player);
    // loadAudios();
    tmx_map* map = LoadTMX(LEVEL_ONE_PATH);

<<<<<<< Updated upstream
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
        ClearBackground(RAYWHITE);
        EndMode2D();
        drawInputEffect();
        drawPlayerStat();
        EndDrawing();
        }
    destroyPlayer();
=======
    // Enemy* e = spawnEnemy();
    Camera2D* cam = initCamera();
    RenderTmxMapToFramebuf(LEVEL_ONE_PATH, &mapFrameBuffer);
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        tickPlayer(&player);
        handleInput();
        // updatePhysics(&delta);
        updateCamera(getPlayerPhysicsObject(player));

        BeginDrawing();
            BeginMode2D(*cam);
                DrawTextureRec(
                  mapFrameBuffer.texture,
                  (Rectangle){0, 0, mapFrameBuffer.texture.width, -mapFrameBuffer.texture.height},
                  (Vector2){0.0, 0.0},
                  WHITE
                );
                animateSprite();
                drawMagic();
                // drawPhysicsRect(getPlayerPhysicsObject(player), BLUE);
                ClearBackground(RAYWHITE);
            EndMode2D();
            drawInputEffect();
            drawPlayerStat(player);
        EndDrawing();
    }
    destroyPlayer(&player);
>>>>>>> Stashed changes
    destroyAnimatedSprites();
    destroyPhysicsObjects();
    destroyMagics();
    UnloadRenderTexture(mapFrameBuffer);
    // unLoadMap(map);
    CloseWindow();
    return 0;
}


void drawInputEffect(){
    if(!isInputBuffEmpty()) {
        DrawText(getInputBuff(), 190, 200, 20, BLACK);
    }
}

void drawPlayerStat(Player player) {
    DrawText(TextFormat("Health: %d, Mana: %d", getPlayerHealth(player), getPlayerMana(player)), 0, 0, 20, BLACK);
    DrawText(TextFormat("X: %f, Y: %f", getPlayerPhysicsObject(player)->pos->x, getPlayerPhysicsObject(player)->pos->y), 0, 20, 20, BLACK);
}