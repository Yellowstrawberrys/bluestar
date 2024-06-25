//
// Created by 정은수 on 2024. 6. 18..
//

#ifndef PHYSICS_H
#define PHYSICS_H
#include "raylib.h"

typedef struct _physicsObject {
    int id;
    Vector2 *pos, force;
    int width, height;
    int facing, type;

    void (*onCollide)(struct _physicsObject*);

    float weight;
} PhysicsObject;

int initPhysics();
void updatePhysics(const float* delta);
PhysicsObject* generatePhysicsObject(Vector2* pos, const int width, const int height, const float weight);
void unregisterPhysicsObject(const PhysicsObject* object);

#endif //PHYSICS_H
