//
// Created by 정은수 on 2024. 6. 19..
//

#include "animation.h"

#include <stdlib.h>

#include "bsutils.h"

List* sprites = createList();


void animateSprite() {
    const LNode* node = sprites->head;
    for (int i=0; i<sprites->size-1; i++) {
        const AnimatedSprite* as = node->address;

        DrawTextureRec(*as->texture, *as->range, *as->coordinate, WHITE);

        node = node->next;
    }
}



AnimatedSprite* generateAnimatedSprite(Texture2D* texture, Rectangle* range, Vector2* coordinate, int count, int fps) {
    AnimatedSprite* sprite = malloc(sizeof AnimatedSprite);
    sprite->texture = texture;
    sprite->range = range;
    sprite->coordinate = coordinate;
    sprite->count = count;
    sprite->fps = fps;
    sprite->current = 0;
    return sprite;
}

void destroyAnimatedSprite(const AnimatedSprite* sprite) {
    removeFromListByAddress(sprites, sprite);
}