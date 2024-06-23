#include <raylib.h>
#include "inputhandle.h"
#include "player.h"
#include "map.h"
#include "tmx_/raytmx.h"

typedef enum _state {

} State;

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080


int main(int argc, char *argv[]) {
    SetTargetFPS(60);
    InitWindow(640, 480, "푸른별");
    InitAudioDevice();
    tmx_map* map = NULL;
    initMap(argc, argv, &map);

    if(map == NULL){ //eRRoR
        CloseWindow();
        return -1;
    }

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        handleInput();
        loadMap(map, SCREENWIDTH, SCREENHEIGHT);
    }
    
    unLoadMap(map);
    CloseWindow();

    return 0;
}


