//
// Created by konod on 2024-06-19.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../animation.h"
#include "../physics.h"

#define G 400
#define PLAYER_JUMP_F 20.0f
#define PLAYER_MAX_SPEED 20.0f
#define PLAYER_MAX_HP 100.0f
#define PLAYER_MAX_MANA 200.0f

typedef struct{
    Vector2 pos;
    PhysicsObject* physics;
    AnimatedSprite* sprite;
    Rectangle* frameRec;
    int health, mana;
    int canJump, f;
} Player;

void tickPlayer(Player* player);
void initPlayer(Texture2D* texture, Player* player);
void jumpPlayer(Player* player);
void movePlayer(const int modifier, Player* player);
void destroyPlayer(Player* player);
int getPlayerHealth(Player player);
int getPlayerMana(Player player);
void heal(const int i, Player* player);
int useMana(const int i, Player* player);
void shootMagic(int type, Player player);
PhysicsObject* getPlayerPhysicsObject(Player player);
AnimatedSprite* getPlayerSprite(Player player);

#endif //PLAYER_H