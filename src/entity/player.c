#include "raylib.h"
#include "player.h"

#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "magic.h"
#include "../animation.h"
#include "../physics.h"
#include "../utils/bsutils.h"
#include "../cameraman.h"

Vector2 pos = {350.0f, 200.0f};
PhysicsObject* physics;
Texture2D texture[2];
AnimatedSprite* sprite;

int health = PLAYER_MAX_HP, mana = PLAYER_MAX_MANA;
int canJump = 1, f=0, mt=-1, fm=0;

void tickPlayer() {
    if(mana>=PLAYER_MAX_MANA) return;
    f++;
    if(f>40) {mana++;f=0;}
    if(mt != -1) fm++;
    if(fm>13 && mt != -1) {
        switch (mt) {
            case 0:
                spawnMagic((Vector2) {pos.x+35*physics->facing, pos.y - physics->height}, 10*physics->facing)->physics->type=1;
            break;
            case 1:
                spawnMagic((Vector2) {pos.x+35*physics->facing, pos.y - physics->height}, 10*physics->facing)->physics->type=2;
            break;
            default: break;
        }
        mt = -1;
        fm = 0;
    }
}

void onPhysicsUpdate(Vector2 changed) {
    if(sprite->type == 0 && fabsf(changed.x) > 0) {
        sprite->pause = 0;
    }else if(sprite->type == 0) {
        sprite->pause = 1;
    }

    if(pos.y >= 300) canJump = 1;
}



void initPlayer() {
    texture[0] = LoadTexture("../Assets/character/walk.png");
    texture[1] = LoadTexture("../Assets/character/magic.png");
    sprite = generateAnimatedSprite(&pos, 2);
    addToAList(sprite->animations, generateAnimation(&texture[0], (Rectangle) {0, 0, texture[0].width/4, texture[0].height}, 4, 7, 1));
    addToAList(sprite->animations, generateAnimationWithOffset(&texture[1], (Rectangle) {0, 0, texture[1].width/5, texture[1].height}, 5, 10, (Vector2) {23, 0}, 0));
    sprite->type = 0;
    sprite->pause = 1;
    physics = generatePhysicsObject(&pos, 20, 40, 10);
    physics->onPhysicsUpdate = &onPhysicsUpdate;
}

PhysicsObject* getPlayerPhysicsObject() {
    return physics;
}

AnimatedSprite* getPlayerSprite() {
    return sprite;
}

void heal(const int i) {
    health = imin(100, health+i);
}

int useMana(const int i) {
    if(mana-i >= 0 ) {
        mana -= i;
        return 1;
    }
    return 0;
}

int getPlayerHealth() {
    return health;
}

int getPlayerMana() {
    return mana;
}

void jumpPlayer() {
    if(!canJump) return;
    physics->force.y -= PLAYER_JUMP_F;
    canJump = 0;
}


void shootMagic(const int type) {
    addCameraOffset( (Vector2) {5*physics->facing, 0});
    sprite->type = 1;
    sprite->current = 0;
    sprite->pause = 0;
    mt = type;
}

void movePlayer(const int modifier) {
    physics->facing = modifier;
    sprite->flipMod = modifier;
    if(fabsf(physics->force.x) < PLAYER_MAX_SPEED) physics->force.x += 2*modifier;
}

void destroyPlayer() {
    UnloadTexture(texture[0]);
    UnloadTexture(texture[1]);
    destroyAnimatedSprite(sprite);
}