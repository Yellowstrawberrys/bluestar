//
// Created by 정은수 on 2024. 6. 13..
//
#include <stdlib.h>
#include "raylib.h"
#include "physics.h"

#include <stdio.h>

#include "utils/bsutils.h"

#define GRAVITY 9.81


void collideCheck(const PhysicsObject* o);


List* physicsObjects;

int initPhysics() {
    physicsObjects = createList();
    return 1;
}

void updatePhysics(const float *delta) {
    const LNode* node = physicsObjects->head;
    for(int i = 0; i < physicsObjects->size; i++) {
        PhysicsObject* p = ((PhysicsObject*) node->address);
        // p->force.y += GRAVITY;
        if(p->force.x > 0) {
            p->force.x = imax(p->force.x-p->weight**delta, 0);
        }else if(p->force.x < 0) {
            p->force.x = imin(p->force.x+p->weight**delta, 0);
        }
        // 0 -> 안부디침
        // 1 -> X
        // 2 -> Y
        // switch (collideMap(((PhysicsObject*) node->address)->coordinate)) {
        //     case 0: ((PhysicsObject*) node->address)->force.y -= GRAVITY; break;
        //     case 1: case -1: ((PhysicsObject*) node->address)->force.x = 0; break;
        //     case 2: case -2: ((PhysicsObject*) node->address)->force.y = 0; break;
        //     default: break;
        // }

        p->pos->x += p->force.x;
        p->pos->y += p->force.y;

        collideCheck(p);
        node = node->next;
    }
}

void collideCheck(const PhysicsObject* o) {
    if(o->onCollide) { //?
        const LNode* node = physicsObjects->head;
        for(int i = 0; i < physicsObjects->size; i++) {
            if(node->address == o) continue;
            PhysicsObject* p = ((PhysicsObject*) node->address);
            float const asy = p->pos->y-p->height/2, aey= p->pos->y+p->height/2;
            float const bsy = o->pos->y-o->height/2, bey= o->pos->y+o->height/2;

            if(
            //      start X (p)           end X (o)             start X (o)          end X (p)
                p->pos->x-p->width <= o->pos->x+o->width && o->pos->x-o->width <= p->pos->x+p->width &&
                p->pos->y-p->height <= o->pos->y+o->height && o->pos->y-o->height <= p->pos->y+p->height
            ) {
                printf("collide\n");
                o->onCollide(p);
            }
            node = node->next;
        }
    }
}

PhysicsObject* generatePhysicsObject(Vector2* pos, const int width, const int height, const float weight) {
    PhysicsObject* p = malloc(sizeof(PhysicsObject));
    p->pos = pos;
    p->width = width;
    p->height = height;
    p->force.x = 0;
    p->force.y = 0;
    p->facing = 0;
    p->type = 0;
    p->weight = weight;
    addToList(physicsObjects, p);
    return p;
}

void unregisterPhysicsObject(const PhysicsObject* object) {
    removeFromListByAddress(physicsObjects, object);
}
