#include "MapCollision.h"
#include "TmxCollisionMapper.h"
#include <stdlib.h>
#include <stdio.h>
//#define NDEBUG
#include <assert.h>




CollisionBoxes* initCollisionBoxes(const char* tmxFileName, Vector2 origin, float scale, tmx_resource_manager* resource_manager, int layerId) {

    printf("\n\n\n----------initializing CollisionBoxes----------\n\n\n\n");
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
    printf("%d\n\n\n",mapData->collisionTilesCount);
    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        currentCollision = mapData->collisionTiles+i;
        currentCollisionData = currentCollision->collisionData;

        //Set position and dimensions of collision boxes
        while (currentCollisionData != NULL) {
            currentRect = collisionBoxes->scaledCollision+currentIndex;
            currentRect->x = origin.x + (( currentCollision->xPos  + currentCollisionData->x )  * scale  );
            currentRect->y = origin.y + ((  currentCollision->yPos + currentCollisionData->y )  * scale  );
            currentRect->width = 32;
            currentRect->height = 32;
            printf("\n\n\n\n\n\n\n\n%d %d\n\n\n\n\n\n\n\n",currentCollision->xPos, currentCollision->yPos);
            currentCollisionData = currentCollisionData->next;
            currentIndex++;
        }
    }
    unloadRawMapData(mapData);
    return collisionBoxes;
}


void unloadMapCollision(CollisionBoxes *collisionBoxes) {
    printf("\n\n\n----------unloading collision----------\n\n\n\n");
    free(collisionBoxes->scaledCollision);
    free(collisionBoxes);
}
