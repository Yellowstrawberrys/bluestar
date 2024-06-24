#ifndef MAP_H
#define MAP_H
#include <tmx.h>

typedef struct _staticObject {
    Rectangle rec;
    int material;
} StaticObject;

void initMap(int argc, char *argv[], tmx_map** map);
void loadMap(tmx_map* map, const int Width, const int Height);
void unLoadMap(tmx_map* map);

#endif //MAP_H