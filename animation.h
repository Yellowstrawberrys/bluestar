//
// Created by 정은수 on 2024. 6. 19..
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include "raylib.h"

typedef struct _animatedSprite {
    Texture2D* texture;
    Rectangle* range;
    Vector2* coordinate;
    int count, fps, current;
} AnimatedSprite;

void animateSprite();
AnimatedSprite* generateAnimatedSprite(Texture2D* texture, Rectangle* range, Vector2* coordinate, int count, int fps);
void destroyAnimatedSprite(const AnimatedSprite* sprite);

#endif //ANIMATION_H
