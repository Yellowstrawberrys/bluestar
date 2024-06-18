//
// Created by 정은수 on 2024. 6. 13..
//
#include <stdlib.h>
#include "bsutils.h"
#include "raylib.h"
#include "map.h"

#define GRAVITY 9.81

typedef struct _physicsObject {
    int id;
    Vector2 coordinate;
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
        if(doesCollideWithMap(&((PhysicsObject*) (node->address))->coordinate)) {

        }
        node = node->next;
    }
}

PhysicsObject* generatePhysicsObject() {
    return malloc(sizeof(PhysicsObject));
}
