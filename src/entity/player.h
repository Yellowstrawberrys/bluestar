//
// Created by konod on 2024-06-19.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../animation.h"
#include "../physics.h"

#define G 400
#define PLAYER_JUMP_F 15.0f
#define PLAYER_MAX_SPEED 10.0f
#define PLAYER_MAX_HP 100.0f
#define PLAYER_MAX_MANA 200.0f

void tickPlayer();
void initPlayer();
void jumpPlayer();
void movePlayer(const int modifier);
void destroyPlayer();
int getPlayerHealth();
int getPlayerMana();
void heal(const int i);
int useMana(const int i);
void shootMagic(int type);
PhysicsObject* getPlayerPhysicsObject();
AnimatedSprite* getPlayerSprite();

#endif //PLAYER_H