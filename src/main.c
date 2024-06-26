#include <stdlib.h>

#include "raylib.h"
#include "tmx.h"
// #include "map.h"

#define TUTORIAL_PATH "../Assets/levels/tutorial_level.tmx"


Texture2D *LoadMapTexture(const char *fileName);

void UnloadMapTexture(Texture2D *tex);

void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);

// Frame buffer into which the map is rendered
RenderTexture2D mapFrameBuffer;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1920;
    int screenHeight = 1080;
    Vector2 player;     // This player doesn't have a box or a sprite. It's just a point.
    Camera2D camera;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    // Load Tiled TMX map and render it to the frame buffer
    RenderTmxMapToFramebuf(TUTORIAL_PATH, &mapFrameBuffer);

    player.x = screenWidth / 2;
    player.y = screenHeight / 2;
    camera.target = (Vector2){ player.x, player.y };
    camera.offset = (Vector2){ 1920, 1080 };
    camera.rotation = 0.0;
    camera.zoom = 1.0;


    while (!WindowShouldClose())
    {
        camera.target = (Vector2){ player.x, player.y };
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                DrawTextureRec(
                    mapFrameBuffer.texture,
                    (Rectangle){0, 0, mapFrameBuffer.texture.width, -mapFrameBuffer.texture.height},
                    (Vector2){0.0, 0.0},
                    WHITE);
            EndMode2D();
        EndDrawing();
    }

    UnloadRenderTexture(mapFrameBuffer);
    CloseWindow();
    return 0;
}