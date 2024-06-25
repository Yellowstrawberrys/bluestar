//
// Created by 정은수 on 2024. 6. 19..
//

#include "animation.h"

#include <stdio.h>
#include <stdlib.h>

#include "bsutils.h"

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
        DrawTextureRec(*as->texture, *as->range, (Vector2) {as->coordinate->x-as->range->width/2, as->coordinate->y-as->range->height/2}, WHITE);
        if(as->count == 0 || as->pause) continue;

        if(frameCount%as->fps==0) {
            as->range->x = as->range->width * as->current;
            if(as->current < as->count-1) as->current++;
            else as->current = 0;
        }
        node = node->next;
    }while (node);
    frameCount++;
}



AnimatedSprite* generateAnimatedSprite(Texture2D* texture, Rectangle* range, Vector2* coordinate, const int count, const int fps) {
    AnimatedSprite* sprite = malloc(sizeof(AnimatedSprite));
    sprite->texture = texture;
    sprite->range = range;
    sprite->coordinate = coordinate;
    sprite->pause = 0;
    sprite->count = count;
    sprite->fps = 60/fps;
    sprite->current = 0;
    addToList(sprites, sprite);
    return sprite;
}

void destroyAnimatedSprite(AnimatedSprite* sprite) {
    removeFromListByAddress(sprites, sprite);
    free(sprite);
}