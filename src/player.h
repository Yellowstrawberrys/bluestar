//
// Created by konod on 2024-06-19.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "physics.h"

#define G 400
#define PLAYER_JUMP_F 350.0f
#define PLAYER_MAX_SPEED 200.0f
#define PLAYER_MAX_HP 100.0f
#define PLAYER_MAX_MANA 200.0f

void initPlayer(Texture2D texture);
void jumpPlayer();
void movePlayer(const int modifier);
void destroyPlayer();
PhysicsObject* getPlayerPhysicsObject();

#endif //PLAYER_H