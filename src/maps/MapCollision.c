#include "MapCollision.h"
#include "TmxCollisionMapper.h"
#include <stdlib.h>
#include <stdio.h>
//#define NDEBUG
#include <assert.h>




CollisionBoxes* initCollisionBoxes(const char* tmxFileName, Vector2 origin, float scale, tmx_resource_manager* resource_manager, int layerId) {

    MapCollisionData* mapData = getRawMapData(resource_manager, tmxFileName, layerId);

    //Initialize collision data
    CollisionBoxes *collisionBoxes = malloc(sizeof(CollisionBoxes));
    collisionBoxes->amountCollisionBoxes = 0;

    //Count collision boxes
    tmx_object* collision = NULL;
    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        collision = mapData->collisionTiles[i].collisionData;
        while (collision != NULL) {
            collisionBoxes->amountCollisionBoxes++;
            collision = collision->next;
        }
    }
    //Initialize collision boxes
    collisionBoxes->scaledCollision = malloc(sizeof(Rectangle) * collisionBoxes->amountCollisionBoxes);
    collisionBoxes->scale = scale;
    Rectangle* currentRect = NULL;
    TileWithCollisionData* currentCollision = NULL;
    tmx_object* currentCollisionData = NULL;
    int currentIndex = 0;
    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        currentCollision = mapData->collisionTiles+i;
        currentCollisionData = currentCollision->collisionData;
        
        //Set position and dimensions of collision boxes
        while (currentCollisionData != NULL) {
            currentRect = collisionBoxes->scaledCollision+currentIndex;
            currentRect->x = origin.x + (( currentCollision->xPos * *mapData->tileWidth + currentCollisionData->x )  * scale  );
            currentRect->y = origin.y + ((  currentCollision->yPos * *mapData->tileHeight + currentCollisionData->y )  * scale  );
            currentRect->width = currentCollisionData->width * scale;
            currentRect->height = currentCollisionData->height * scale;
            currentCollisionData = currentCollisionData->next;
            currentIndex++;
        }
    }
    unloadRawMapData(mapData);
    return collisionBoxes;
}


void unloadMapCollision(CollisionBoxes *collisionBoxes) {
    free(collisionBoxes->scaledCollision);
    free(collisionBoxes);
}
