#include "TmxCollisionMapper.h"
#include <stdbool.h>
#include <stdlib.h>


int getAmountOfTilesWithCollision(tmx_map* map, tmx_layer* layer);

MapCollisionData* getRawMapData(tmx_resource_manager* rm, const char *tmxFileName, int layerid) {
    int targetGid = 0;
    tmx_tile* currentTile;

    tmx_map* map = tmx_rcmgr_load(rm,tmxFileName);

    MapCollisionData* collisionData = malloc(sizeof(MapCollisionData));
    collisionData->map = map;
    collisionData->tileHeight = &map->ts_head->tileset->tile_height;
    collisionData->tileWidth = &map->ts_head->tileset->tile_width;
    //TODO Tileset Offset

    tmx_layer* currentLayer = map->ly_head;
    while (currentLayer->id != layerid ) {
        currentLayer = currentLayer->next;
    }

    collisionData->collisionTilesCount = getAmountOfTilesWithCollision(map, currentLayer);

    collisionData->collisionTiles = malloc(collisionData->collisionTilesCount*sizeof(TileWithCollisionData));

    //Fill structure/array with collision data
    int collisionTilesCounter = 0;
    for (int row = 0; row < map->height; row++) {
        for (int column = 0; column < map->width; column++) {
            targetGid = *(currentLayer->content.gids+(row*map->width+column));
            currentTile = map->tiles[targetGid];
            if (currentTile->collision != NULL) {
                (collisionData->collisionTiles+collisionTilesCounter)->collisionData = currentTile->collision;   
                (collisionData->collisionTiles+collisionTilesCounter)->xPos = column;
                (collisionData->collisionTiles+collisionTilesCounter)->yPos = row;                    
                collisionTilesCounter++;                    
            }
        }  
    }

    return collisionData;
}

int getAmountOfTilesWithCollision(tmx_map* map, tmx_layer* layer) {
    int targetGid = 0;
    int counter = 0;
    tmx_tile* currentTile;
    for (int row = 0; row < map->height; row++) {
        for (int column = 0; column < map->width; column++) {
            targetGid = *(layer->content.gids+(row*map->width+column));
            currentTile = map->tiles[targetGid];
            if (currentTile->collision != NULL) {
                counter++;
            }
        }  
    }
    return counter;
}


void unloadRawMapData(MapCollisionData* mapData) {
    free(mapData->collisionTiles);
    tmx_map_free(mapData->map);
    free(mapData);
}
