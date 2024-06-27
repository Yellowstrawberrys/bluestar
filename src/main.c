#include <raylib-tmx.h>
#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>

#include "animation.h"
#include "audioman.h"
#include "cameraman.h"
#include "inputhandle.h"
#include "utils/debugutils.h"
#include "physics.h"
#include "entity/enemy.h"
#include "entity/magic.h"
#include "entity/player.h"
#include "tmx.h"
#include "maps/MapCollision.h"

#define RAYLIB_TMX_IMPLEMENTATION
#define TUTORIAL_PATH "../Assets/levels/tutorial_level.tmx"
#define LEVEL_ONE_PATH "../Assets/levels/level_one.tmx"

#define SCREENWIDTH 1920/2
#define SCREENHEIGHT 1080/2

void initDrawInputEffect();

Texture2D *LoadMapTexture(const char *fileName);

void UnloadMapTexture(Texture2D *tex);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
void drawInputEffect();
void drawPlayerStat(Player* player);
void initPlayerRec(Player player, Rectangle* playerRec);

RenderTexture2D mapFrameBuffer;

int a = 0;
int playerState;
const int scaleMultiplier = 32;

int main(int argc, char *argv[]) {
    printf("main function started\n");
    Player player;
    SetTargetFPS(60);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "푸른별");
    InitAudioDevice();
    initAnimationSprites();
    initPhysics();
    initMagics();
    initDrawInputEffect();
    RenderTexture2D backgroundTexture = LoadRenderTexture(1920 ,1080);
    RenderTexture2D renderAll = LoadRenderTexture(32,32);
    initEnemy();
    tmx_map* map = LoadTMX(LEVEL_ONE_PATH);

    tmx_resource_manager* rm = tmx_make_resource_manager();

    DrawTMX(map,0,0,WHITE);

    CollisionBoxes *boxes = initCollisionBoxes(LEVEL_ONE_PATH, (Vector2){0.0f, 0.0f}, scaleMultiplier, rm, 1);
    initPlayer(&player);
    loadAudios();
    Rectangle playerRect = {
        player.pos.x-player.physics->width,
        player.pos.y-player.physics->height,
        player.physics->width*2,
        player.physics->height*2
    };

    Enemy* e = spawnEnemy((Vector2){500, 200});
    Camera2D* cam = initCamera();
    RenderTmxMapToFramebuf(LEVEL_ONE_PATH, &mapFrameBuffer);

    while (!WindowShouldClose()) {
        initPlayerRec(player, &playerRect);
        float delta = GetFrameTime();
        BeginTextureMode(renderAll);
            DrawTexturePro(backgroundTexture.texture,
                            (Rectangle){ 0.0f, 0.0f, (float)backgroundTexture.texture.width, (float)-backgroundTexture.texture.height },
                            (Rectangle){ (0.0f), (0.0f),backgroundTexture.texture.width * scaleMultiplier, backgroundTexture.texture.height * scaleMultiplier},
                            (Vector2){ 0, 0 },
                            0.0f,
                            WHITE);
            DrawRectanglePro(playerRect,(Vector2){0,0},0.0f,BLACK);
        EndTextureMode();
        tickPlayer();
        handleInput();
        updatePhysics(&delta);
        updateCamera(getPlayerPhysicsObject());

        BeginDrawing();
            BeginMode2D(*cam);
                DrawTextureRec(
                  mapFrameBuffer.texture,
                  (Rectangle){0, 0, mapFrameBuffer.texture.width, -mapFrameBuffer.texture.height},
                  (Vector2){0.0, 0.0},
                  WHITE
                  );

                // Draw collision rectangles
                for (int i = 0; i < boxes->amountCollisionBoxes; i++) {
                    Rectangle *currentRectangle = boxes->scaledCollision + i;
                    DrawRectangleLines(currentRectangle->x, currentRectangle->y, currentRectangle->width, currentRectangle->height, BLUE);
                    checkPlayerTileCollision(&player, *currentRectangle, playerRect);
                }

                animateSprite();
                drawMagic();
                drawPhysicsRect(getPlayerPhysicsObject(), BLACK);
                ClearBackground(RAYWHITE);
            EndMode2D();
            drawInputEffect();
            drawPlayerStat(&player);
        EndDrawing();
    }
    destroyPlayer();
    destroyEnemies();
    destroyMagics();
    destroyAnimatedSprites();
    destroyPhysicsObjects();
    unloadAudios();
    tmx_free_resource_manager(rm);
    UnloadRenderTexture(mapFrameBuffer);
    UnloadTMX(map);
    CloseWindow();
    printf("main function finished\n");
    return 0;
}

Texture2D inputTextures[2];

void initDrawInputEffect() {
    inputTextures[0] = LoadTexture("../Assets/input/bg.png");
    inputTextures[1] = LoadTexture("../Assets/input/letters.png");
}

void drawInputEffect(){
    if(!isInputBuffEmpty()) {
        const int sx = SCREENWIDTH/2-inputTextures[0].width*1.5, sy = SCREENHEIGHT/8-inputTextures[0].height*1.5;
        DrawTexturePro(inputTextures[0], (Rectangle) {0, 0, inputTextures[0].width, inputTextures[0].height}, (Rectangle) {sx, sy, inputTextures[0].width*3, inputTextures[0].height*3}, (Vector2) {0,0}, 0, WHITE);
        for(int i = 0; i<4 && getInputBuff()[i]!='\0'; i++) {
            DrawTexturePro(
                inputTextures[1],
                (Rectangle) {14*(getInputBuff()[i]=='l'?0:getInputBuff()[i]=='k'?1:getInputBuff()[i]=='i'?2:3), 0, inputTextures[1].width/4, inputTextures[1].height},
                (Rectangle) {sx+21+(inputTextures[1].width/4+3)*3*i, sy+30, inputTextures[1].width/4*3, inputTextures[1].height*3},
                (Vector2) {0,0}, 0, WHITE
                );
        }
    }
}

void drawPlayerStat(Player* player) {
    printf("drawPlayerStat called\n");
    DrawText(TextFormat("Health: %d, Mana: %d", getPlayerHealth(), getPlayerMana()), 0, 0, 20, BLACK);
    DrawText(TextFormat("X: %f, Y: %f", getPlayerPhysicsObject()->pos->x, getPlayerPhysicsObject()->pos->y), 0, 20, 20, BLACK);
}

void initPlayerRec(Player player, Rectangle* playerRec) {
    playerRec->x = player.pos.x-player.physics->width;
    playerRec->y = player.pos.y-player.physics->height;
    playerRec->width = player.physics->width*2;
    playerRec->height = player.physics->height*2;
}