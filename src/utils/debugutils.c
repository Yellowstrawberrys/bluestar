//
// Created by 정은수 on 2024. 6. 25..
//

#include "debugutils.h"

void drawPhysicsRect(const PhysicsObject* o, Color c) {
    DrawRectangleLines(o->pos->x-o->width, o->pos->y-o->height, o->width*2, o->height*2, c);
}