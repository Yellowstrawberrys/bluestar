//
// Created by 정은수 on 2024. 6. 19..
//

#include "animation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils/bsutils.h"

List* sprites;
int frameCount = 0;

int initAnimationSprites() {
    sprites = createList();
    return 1;
}

void animateSprite() {
    const LNode* node = sprites->head;

    do {
        AnimatedSprite* as = node->address;
        as->range->x = as->range->width * as->current;
        as->range->width = fabsf(as->range->width)*as->flipMod;
        DrawTexturePro(*as->texture, *as->range,
            (Rectangle) {as->coordinate->x, as->coordinate->y, as->range->width*as->flipMod, as->range->height},
            (Vector2) {as->range->width/2*as->flipMod, as->range->height/2}, 0, WHITE
        );
        if(as->count == 0 || as->pause) {node = node->next;continue;}

        if(frameCount%as->fps==0) {
            if(as->current < as->count-1) as->current++;
            else as->current = 0;
        }
        node = node->next;
    }while (node);
    frameCount++;
}



AnimatedSprite* generateAnimatedSprite(Texture2D* texture, Rectangle range, Vector2* coordinate, const int count, const int fps) {
    AnimatedSprite* sprite = malloc(sizeof(AnimatedSprite)); // B - AnimatedSprite (1)
    sprite->range = malloc(sizeof(Rectangle)); // B - Rectangle (1)
    sprite->range->x = range.x;
    sprite->range->y = range.y;
    sprite->range->width = range.width;
    sprite->range->height = range.height;
    sprite->texture = texture;
    sprite->coordinate = coordinate;
    sprite->pause = 0;
    sprite->count = count;
    sprite->fps = 60/fps;
    sprite->current = 0;
    sprite->flipMod = 1;
    addToList(sprites, sprite);
    return sprite;
}

void destroyAnimatedSprite(AnimatedSprite* sprite) {
    removeFromListByAddress(sprites, sprite);
    free(sprite->range); // R - Rectangle (1)
    free(sprite); // R - AnimatedSprite (1)
}

void destroyAnimatedSprites() {
    LNode* node = sprites->head;
    while (node) {
        free(node->address); // R - Enemy (1)
        node = node->next;
    }
    destroyList(sprites);
}