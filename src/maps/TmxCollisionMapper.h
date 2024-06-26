#ifndef TMX_COLLISION_MAPPER_H
#define TMX_COLLISION_MAPPER_H
#include "include/tmx.h"

typedef struct TileWithCollisionData{
    int xPos;
    int yPos;
    tmx_object *collisionData;
} TileWithCollisionData;

typedef struct MapCollisionData{
    tmx_map* map;
    TileWithCollisionData* collisionTiles;
    int collisionTilesCount;
    int* tileWidth;
    int* tileHeight;
} MapCollisionData;

MapCollisionData* getRawMapData(tmx_resource_manager* rm, const char *tmxFileName, int layerid);
void unloadRawMapData(MapCollisionData* mapData);


#endif
