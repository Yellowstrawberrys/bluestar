#ifndef MAP_H
#define MAP_H

typedef struct _staticObject {
    Rectangle rec;
    int material;
} StaticObject;

int doesCollideWithMap(Vector2 vec);

#endif //MAP_H