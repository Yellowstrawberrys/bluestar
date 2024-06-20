//
// Created by 정은수 on 2024. 6. 19..
//

#include "animation.h"

#include <stdlib.h>

#include "bsutils.h"

List* sprites = createList();
int frameCount = 0;

void animateSprite() {
    const LNode* node = sprites->head;
    for (int i=0; i<sprites->size-1; i++) {
        AnimatedSprite* as = node->address;
        if(as->count == 0) continue;

        DrawTextureRec(*as->texture, *as->range, *as->coordinate, WHITE);
        as->range->x = as->range->x * as->current;

        if(frameCount%(60/as->fps)==0) {
            if(as->current < as->count) as->current++;
            else as->current = 0;
        }


        node = node->next;
    }
    frameCount++;
}



AnimatedSprite* generateAnimatedSprite(Texture2D* texture, Rectangle* range, Vector2* coordinate, int count, int fps) {
    AnimatedSprite* sprite = malloc(sizeof (AnimatedSprite));
    sprite->texture = texture;
    sprite->range = range;
    sprite->coordinate = coordinate;
    sprite->count = count;
    sprite->fps = fps;
    sprite->current = 0;
    addToList(sprites, sprite);
    return sprite;
}

void destroyAnimatedSprite(const AnimatedSprite* sprite) {
    removeFromListByAddress(sprites, sprite);
}