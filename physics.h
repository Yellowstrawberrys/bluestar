//
// Created by 정은수 on 2024. 6. 18..
//

#ifndef PHYSICS_H
#define PHYSICS_H
#include "raylib.h"

typedef struct _physicsObject {
    int id;
    Vector2 coordinate, force;
    int facing;

    void (*onCollide)(struct _physicsObject*);

    float weight;
} PhysicsObject;

void updatePhysics();
PhysicsObject* generatePhysicsObject();
void unregisterPhysicsObject(const PhysicsObject* object);

#endif //PHYSICS_H
