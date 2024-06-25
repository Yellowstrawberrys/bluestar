//
// Created by 정은수 on 2024. 6. 26..
//

#include "magic.h"

#include <stdlib.h>
#include <time.h>

#include "../utils/bsutils.h"
#include "../utils/debugutils.h"

List* magics;

int initMagics() {
    magics = createList();
    return 1;
}

Magic* spawnMagic(const Vector2 loc, const int modifier) {
    Magic* m = (Magic*) malloc(sizeof(Magic));
    Vector2* vec = malloc(sizeof(Vector2));
    vec->x = loc.x;
    vec->y = loc.y;
    m->physics = generatePhysicsObject(vec, 15,15, 0);
    m->physics->force.x = modifier;
    addToList(magics, m);
    return m;
}

void drawMagic() {
    srand(time(NULL));
    const LNode* node = magics->head;
    while (node) {
        for(int x =0; x<5; x++) {
            for(int i =0; i<x*2; i++) {
                DrawCircleGradient(((Magic*)node->address)->physics->pos->x+(rand()%10-5) + i*((Magic*)node->address)->physics->force.x,((Magic*)node->address)->physics->pos->y+(rand()%(10*x)-5*x), 5, WHITE, YELLOW);
            }
        }

        drawPhysicsRect(((Magic*)node->address)->physics, RED);
        ((Magic*)node->address)->age++;
        if(((Magic*)node->address)->age > 60*10) {
            LNode* tmp = node->next;
            removeFromListByAddress(magics, node->address);
            node = tmp;
        }else node = node->next;
    }
}

void destroyMagic(Magic* m) {
    removeFromListByAddress(magics, m);
    free(m);
}

void destroyMagics() {
    clearListWithValues(magics);
}