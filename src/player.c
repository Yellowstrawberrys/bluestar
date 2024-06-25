#include "raylib.h"
#include "player.h"

#include <stdio.h>

#include "animation.h"
#include "physics.h"

Vector2 pos = {350.0f, 200.0f};
PhysicsObject* physics;
AnimatedSprite* sprite;

int health = PLAYER_MAX_HP, mana = PLAYER_MAX_MANA;
int canJump = 1;

void initPlayer(Texture2D scarfy) {
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    sprite = generateAnimatedSprite(&scarfy, &frameRec, &pos, 6, 20);
    physics = generatePhysicsObject(&pos, 50, scarfy.height, 10);
}

PhysicsObject* getPlayerPhysicsObject() {
    return physics;
}

void jumpPlayer() {
    if(!canJump) return;
    printf("%f\n", pos.y);
    physics->force.y += PLAYER_JUMP_F;
    canJump = 0;
}

void movePlayer(const int modifier) {
    if(physics->force.x < PLAYER_MAX_SPEED) physics->force.x += 5*modifier;
}

void destroyPlayer() {
    destroyAnimatedSprite(sprite);
}