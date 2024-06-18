//
// Created by 정은수 on 2024. 6. 13..
//
#include <stdlib.h>
#include "bsutils.h"
#include "raylib.h"
#include "map.h"
#include "physics.h"

#define GRAVITY 9.81

List* physicsObjects = createList();

void updatePhysics() {
    const float delta = GetFrameTime();
    const LNode* node = physicsObjects->head;
    for(int i = 0; i < physicsObjects->size; i++) {
        // 0 -> 안부디침
        // 1 -> X
        // 2 -> Y
        switch (collideMap(&((PhysicsObject*) node->address)->coordinate)) {
            case 0: ((PhysicsObject*) node->address)->force.y -= GRAVITY; break;
            case 1: case -1: ((PhysicsObject*) node->address)->force.x = 0; break;
            case 2: case -2: ((PhysicsObject*) node->address)->force.y = 0; break;
            default: break;
        }

        ((PhysicsObject*) node->address)->coordinate.x += ((PhysicsObject*) node->address)->force.x*delta;
        ((PhysicsObject*) node->address)->coordinate.y += ((PhysicsObject*) node->address)->force.y*delta;

        node = node->next;
    }
}

PhysicsObject* generatePhysicsObject() {
    PhysicsObject* p = malloc(sizeof(PhysicsObject));
    addToList(physicsObjects, p);
    return p;
}

void unregisterPhysicsObject(PhysicsObject* object) {

}
