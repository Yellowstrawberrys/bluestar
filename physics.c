//
// Created by 정은수 on 2024. 6. 13..
//
#include <stdlib.h>
#include "bsutils.h"
#include "raylib.h"

#define GRAVITY 9.81

typedef struct _physicsObject {
    int id;
    Vector2 coordinate, force;
    int facing;

    void (*onCollide)(struct _physicsObject*);

    float weight;
} PhysicsObject;

void update();
PhysicsObject* generatePhysicsObject();
void unregisterPhysicsObject(PhysicsObject* object);


List* physicsObjects = createList();

void update() {
    float delta = GetFrameTime();
    const LNode* node = physicsObjects->head;
    for(int i = 0; i < physicsObjects->size; i++) {
        ((PhysicsObject*) (node->address))->dx;
        node = node->next;
    }
}

PhysicsObject* generatePhysicsObject() {
    return malloc(sizeof(PhysicsObject));
}
