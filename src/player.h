//
// Created by konod on 2024-06-19.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "raymath.h"


#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f
#define PLAYER_MAX_HP 100.0f
#define PLAYER_MAX_MANA 200.0f

typedef struct _player {
    Vector2 position;
    float speed;
    float hp;
    float mana;
    bool canJump;
} Player;




int move(Player *player, float delta);
int jump();
int summonPlayer(Player *player, float delta);
int UpdatePlayer(Player *player, float delta);
int UpdateCameraCenter(Camera2D *camera, Player *player, float delta, int width, int height);

#endif //PLAYER_H