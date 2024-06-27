#ifndef MAP_COLLISION_H
#define MAP_COLLISION_H
#include <stdbool.h>
#include "raylib.h"
#include "tmx.h"


typedef struct CollisionBoxes {
    int amountCollisionBoxes;
    Rectangle* scaledCollision;
    float scale;
} CollisionBoxes;

/// @brief Initialize rectangles for every collision in all tiles of specific layer
/// @param tmxFileName The TMX file
/// @param origin Origin for scaling and positioning of the rectangles
/// @param scale Multiplacator for scaling the rectangles
/// @param resource_manager tmx_resource_manager
/// @param layerId The layer where the collision data is placed
/// @return Array with all rectangles
CollisionBoxes* initCollisionBoxes(const char* tmxFileName, Vector2 origin, float scale, tmx_resource_manager* resource_manager, int layerId);
void unloadMapCollision(CollisionBoxes *collisionBoxes);


#endif