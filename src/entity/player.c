#include "raylib.h"
#include "player.h"

#include <math.h>
#include <stdlib.h>

#include "magic.h"
#include "../animation.h"
#include "../physics.h"
#include "../utils/bsutils.h"
#include "../cameraman.h"

Vector2 pos = {350.0f, 200.0f};
PhysicsObject* physics;
AnimatedSprite* sprite;
Rectangle* frameRec;

int health = PLAYER_MAX_HP, mana = PLAYER_MAX_MANA;
int canJump = 1, f=0;

void tickPlayer() {
    if(mana>=PLAYER_MAX_MANA) return;
    f++;
    if(f>40) {mana++;f=0;}
}

void onPhysicsUpdate(Vector2 changed) {
    if(fabsf(changed.x) > 0) {
        sprite->pause = 0;
    }else {
        sprite->current = 0;
        sprite->pause = 1;
    }

    if(pos.y >= 300) canJump = 1;
}

void initPlayer(Texture2D* scarfy) {
    sprite = generateAnimatedSprite(scarfy, (Rectangle) {0, 0, (float)scarfy->width/6, (float)scarfy->height}, &pos, 6, 20);
    sprite->pause = 1;
    physics = generatePhysicsObject(&pos, 50, 60, 10);
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
    switch (type) {
        case 0:
            spawnMagic(pos, 10*physics->facing)->physics->type=1;
            break;
        case 1:
            spawnMagic(pos, 10*physics->facing)->physics->type=2;
            break;
        default: break;
    }
}

void movePlayer(const int modifier) {
    physics->facing = modifier;
    sprite->flipMod = modifier;
    if(fabsf(physics->force.x) < PLAYER_MAX_SPEED) physics->force.x += 2*modifier;
}

void destroyPlayer() {
    destroyAnimatedSprite(sprite);
}