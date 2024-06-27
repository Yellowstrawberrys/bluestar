//
// Created by 정은수 on 2024. 6. 19..
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include "raylib.h"
#include "utils/bsutils.h"

typedef struct _animation {
    Texture2D* texture;
    Rectangle* range;
    Vector2 offset;
    int count, fps, loop, next;
    float scale;
} Animation;

typedef struct _animatedSprite {
    ArrayList* animations;
    Vector2* coordinate;
    int type, pause, current, flipMod, fc;
    float scale;
} AnimatedSprite;

int initAnimationSprites();
void animateSprite();
Animation* generateAnimationWithOffset(Texture2D* texture, const Rectangle range, const int count, const int fps, const Vector2 offset, const int loop);
Animation* generateAnimation(Texture2D* texture, const Rectangle range, const int count, const int fps, const int loop);
void destroyAnimation(Animation* animation);
void destroyAnimationList(ArrayList* l);
AnimatedSprite* generateAnimatedSprite(Vector2* coordinate, const float scale);
void destroyAnimatedSprite(AnimatedSprite* sprite);
void destroyAnimatedSprites();

#endif //ANIMATION_H
