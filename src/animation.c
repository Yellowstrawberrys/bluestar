//
// Created by 정은수 on 2024. 6. 19..
//

#include "animation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils/bsutils.h"

List* sprites;

int initAnimationSprites() {
    sprites = createList();
    return 1;
}

void animateSprite() {
    const LNode* node = sprites->head;

    int l = 0;
    do {
        AnimatedSprite* as = node->address;
        if(as->animations->size == 0) {node = node->next;continue;}


        const Animation* a = getElementFromAList(as->animations, as->type);
        if(a) {
            a->range->x = a->range->width * as->current;
            a->range->width = fabsf(a->range->width)*as->flipMod;
            DrawTexturePro(*a->texture, *a->range,
                (Rectangle) {as->coordinate->x+a->offset.x, as->coordinate->y-(a->range->height*as->scale)+a->offset.y, a->range->width*as->flipMod * as->scale, a->range->height * as->scale},
                (Vector2) {(a->range->width-a->offset.x)*as->scale/2*as->flipMod + a->offset.x, -a->offset.y*as->scale/2*as->flipMod - a->offset.y}, 0, WHITE
            );
            // DrawCircle(as->coordinate->x, as->coordinate->y, 10, RED);

            if(a->count == 0 || as->pause) {node = node->next;continue;}

            if(as->fc>=a->fps) {
                if(l==0) printf("%d %d / %d %d\n", as->type, a->loop, as->current, a->count-1);
                if(as->current < a->count-1) {as->current++; }
                else {
                    if(!a->loop) {as->type = a->next;}
                    as->current = 0;
                }
                as->fc=0;
            }
            as->fc++;
        }
        l++;
        node = node->next;
    }while (node);
}

Animation* generateAnimationWithOffset(Texture2D* texture, const Rectangle range, const int count, const int fps, const Vector2 offset, const int loop) {
    Animation* animation = malloc(sizeof(Animation)); // B - Animation (1)
    animation->texture = texture;
    animation->range = malloc(sizeof(Rectangle)); // B - Rectangle (1)
    animation->range->y = range.y;
    animation->range->width = range.width;
    animation->range->height = range.height;
    animation->count = count;
    animation->fps = 60/fps;
    animation->loop = loop;
    animation->offset = offset;
    return animation;
}

Animation* generateAnimation(Texture2D* texture, const Rectangle range, const int count, const int fps, const int loop) {
    return generateAnimationWithOffset(texture, range, count, fps, (Vector2){0,0}, loop);
}

void destroyAnimation(Animation* animation) {
    free(animation->range); // R - Animation (1)
    free(animation); // B - Rectangle (1)
}

void destroyAnimationList(ArrayList* l) {
    for(int i=0; i<l->size; i++) {
        free(l->elements[i]); // R - Animation (1)
    }
    destroyAList(l); // R - ArrayList (1)
}

AnimatedSprite* generateAnimatedSprite(Vector2* coordinate, const float scale) {
    AnimatedSprite* sprite = malloc(sizeof(AnimatedSprite)); // B - AnimatedSprite (1)
    sprite->animations = createAList(); // B - ArrayList (1)
    sprite->coordinate = coordinate;
    sprite->type = -1;
    sprite->pause = 0;
    sprite->current = 0;
    sprite->flipMod = 1;
    sprite->scale = scale;
    addToList(sprites, sprite);
    return sprite;
}

void destroyAnimatedSprite(AnimatedSprite* sprite) {
    removeFromListByAddress(sprites, sprite);
    destroyAList(sprite->animations); // R - ArrayList (1)
    free(sprite); // R - AnimatedSprite (1)
}

void destroyAnimatedSprites() {
    const LNode* node = sprites->head;
    while (node) {
        destroyAList(((AnimatedSprite*)node->address)->animations); // R - ArrayList (1)
        free(node->address); // R - AnimatedSprite (1)
        node = node->next;
    }
    destroyList(sprites);
}