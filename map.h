#ifndef MAP_H
#define MAP_H

typedef struct _staticObject {
    Rectangle rec;
    int material;
} StaticObject;

int collideMap(Vector2* vec);

#endif //MAP_H