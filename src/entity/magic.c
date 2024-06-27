//
// Created by 정은수 on 2024. 6. 26..
//

#include "magic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../entity/enemy.h"
#include "../utils/bsutils.h"
#include "../utils/debugutils.h"

Magic* findMagicByPhysics(const PhysicsObject* p);


List* magics;

int initMagics() {
    magics = createList();
    return 1;
}

void onHit(PhysicsObject* me, PhysicsObject* hit) {
    printf("type: %d\n", hit->type);
    if(hit->type==3) {
        damageEnemy(hit, 10);
        destroyMagic(findMagicByPhysics(me));
    }
}


Magic* spawnMagic(const Vector2 loc, const int modifier) {
    Magic* m = (Magic*) malloc(sizeof(Magic)); // B - Magic (1)
    Vector2* vec = malloc(sizeof(Vector2)); // B - Vector (1)
    vec->x = loc.x;
    vec->y = loc.y;
    m->physics = generatePhysicsObject(vec, 15,15, 0);
    m->physics->force.x = modifier;
    m->physics->onCollide = onHit;
    addToList(magics, m);
    return m;
}

void drawMagic() {
    const LNode* node = magics->head;
    while (node) {
        for(int x =0; x<5; x++) {
            srand(time(NULL));
            for(int i =0; i<x*2; i++) {
                DrawCircleGradient(((Magic*)node->address)->physics->pos->x+(rand()%10-5) + i*((Magic*)node->address)->physics->force.x,((Magic*)node->address)->physics->pos->y+(rand()%(10*x)-5*x), 5, WHITE, YELLOW);
            }
        }

        drawPhysicsRect(((Magic*)node->address)->physics, RED);
        ((Magic*)node->address)->age++;
        if(((Magic*)node->address)->age > 60*4) {
            LNode* tmp = node->next;
            removeFromListByAddress(magics, node->address);
            node = tmp;
        }else node = node->next;
    }
}

Magic* findMagicByPhysics(const PhysicsObject* p) {
    const LNode* node = magics->head;
    while (node) {
        Magic* magic = (Magic*) node->address;
        if(magic->physics==p) return magic;
        node = node->next;
    }
    return NULL;
}

void destroyMagic(Magic* m) {
    removeFromListByAddress(magics, m);
    Vector2 *vec = m->physics->pos;
    unregisterPhysicsObject(m->physics);
    free(vec); // R - Vector (1)
    free(m); // R - Enemy (1)
}

void destroyMagics() {
    LNode* node = magics->head;
    while (node) {
        Magic* magic = (Magic*) node->address;
        node = node->next;
        Vector2* vec = magic->physics->pos;
        unregisterPhysicsObject(magic->physics);
        free(magic); // R - Enemy (1)
        free(vec); // R - Vector (1)
    }
    destroyList(magics);
}