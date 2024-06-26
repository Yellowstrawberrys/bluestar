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
// #include "map.h"

#define TUTORIAL_PATH "../Assets/levels/tutorial_level.tmx"
#define LEVEL_ONE_PATH "../Assets/levels/level_one.tmx"

#define SCREENWIDTH 1920/2
#define SCREENHEIGHT 1080/2

void initDrawInputEffect();

Texture2D *LoadMapTexture(const char *fileName);

void UnloadMapTexture(Texture2D *tex);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
void drawInputEffect();
void drawPlayerStat();

RenderTexture2D mapFrameBuffer;


int a = 0;

int main(int argc, char *argv[]) {
    SetTargetFPS(60);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "푸른별");
    InitAudioDevice();
    initAnimationSprites();
    initPhysics();
    initMagics();
    initDrawInputEffect();
    initEnemy();

    Texture2D texture = LoadTexture("../Assets/scarfy.png");

    initPlayer(&texture);
    loadAudios();
    tmx_map* map = NULL;

    Enemy* e = spawnEnemy();
    Camera2D* cam = initCamera();
    RenderTmxMapToFramebuf(LEVEL_ONE_PATH, &mapFrameBuffer);
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        tickPlayer();
        handleInput();
        // updatePhysics(&delta);
        updateCamera(getPlayerPhysicsObject());

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
                // drawPhysicsRect(getPlayerPhysicsObject(), BLUE);
                ClearBackground(RAYWHITE);
            EndMode2D();
            drawInputEffect();
            drawPlayerStat();
        EndDrawing();
    }
    destroyPlayer();
    destroyAnimatedSprites();
    destroyPhysicsObjects();
    destroyEnemies();
    destroyMagics();
    unloadAudios();
    UnloadRenderTexture(mapFrameBuffer);
    CloseWindow();
    return 0;
}

Texture2D inputTextures[2];

void initDrawInputEffect() {
    inputTextures[0] = LoadTexture("../Assets/input/bg.png");
    inputTextures[1] = LoadTexture("../Assets/input/letters.png");
}

void drawInputEffect(){
    if(!isInputBuffEmpty()) {
        const int sx = SCREENWIDTH/2-inputTextures[0].width*1.5, sy = SCREENHEIGHT/4-inputTextures[0].height*1.5;
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

void drawPlayerStat() {
    DrawText(TextFormat("Health: %d, Mana: %d", getPlayerHealth(), getPlayerMana()), 0, 0, 20, BLACK);
    DrawText(TextFormat("X: %f, Y: %f", getPlayerPhysicsObject()->pos->x, getPlayerPhysicsObject()->pos->y), 0, 20, 20, BLACK);
}