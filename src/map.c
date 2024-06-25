//
// Created by 정은수 on 2024. 6. 13..
//

#pragma once
#include <raylib.h>
#include "map.h"

#include <raylib-tmx.h>

#include "utils/bsutils.h"
#include "tmx.h"

// List* mapObjects = createList();

// void drawTileLayer(tson::Layer &Layer, const Camera2D &camera, const Vector2 &offset, const Color &tint){
//     auto layerOffset = layer.getOffset();
//     for (auto& [pos, tileobject] : layer.getTileObjects()){
        
//     }
// }
//c++ 코드 보고있었음

void initMap(int argc, char *argv[], tmx_map** map){
    ChangeDirectory(GetDirectoryPath(argv[0]));
    *map = LoadTMX(argc > 1 ? argv[1] : "../Assets/levels/tutorial_level.tmx");
}

void loadMap(tmx_map* map, const int Width, const int Height){
    BeginDrawing();{
        ClearBackground(RAYWHITE);
        DrawTMX(map, Width, Height, WHITE);
        DrawFPS(10, 10);
    }
    EndDrawing();
}

void unLoadMap(tmx_map* map){
    if(map != NULL){
        tmx_map_free(map);
    }
}