//
// Created by konod on 2024-06-19.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "player.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "magic.h"
#include "../animation.h"
#include "../physics.h"
#include "../utils/bsutils.h"
#include "../cameraman.h"
#include "../maps/MapCollision.h"
#include "../maps/TmxCollisionMapper.h"

#define G 400
#define PLAYER_JUMP_F 15.0f
#define PLAYER_MAX_SPEED 10.0f
#define PLAYER_MAX_HP 100.0f
#define PLAYER_MAX_MANA 200.0f
#define PLAYERSPAWNX 350.0f
#define PLAYERSPAWNY 200.0f


typedef struct {
    Vector2 pos;
    PhysicsObject* physics;
    AnimatedSprite* sprite;
    Rectangle* frameRec;
    int health, mana;
    int canJump, f;
    float speed;
} Player;


void tickPlayer();
void initPlayer(Player* player);
void jumpPlayer();
void movePlayer(const int modifier);
void destroyPlayer();
int getPlayerHealth();
int getPlayerMana();
void damagePlayer(const int i);
void heal(const int i);
int useMana(const int i);
void shootMagic(const int type);
PhysicsObject* getPlayerPhysicsObject();
AnimatedSprite* getPlayerSprite();
int checkPlayerTileCollision(Player* player, Rectangle collisionBoxes, Rectangle playerRect);

#endif //PLAYER_H