//
// Created by 정은수 on 2024. 6. 26..
//

#ifndef MAGIC_H
#define MAGIC_H
#include "../physics.h"

typedef struct _magic {
    PhysicsObject* physics;
    int age;
} Magic;

int initMagics();
Magic* spawnMagic(const Vector2 loc, const int modifier);
void drawMagic();
void destroyMagic(Magic* m);
void destroyMagics();

#endif //MAGIC_H
