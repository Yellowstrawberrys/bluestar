//
// Created by konod on 2024-06-19.
//
#pragma once
#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "physics.h"


int summonPlayer(Player *player, float delta){
    player -> position = (Vector2){ 400, 280 };
    player -> speed = 0;
    player -> canJump = false;
}

int updatePlayer(Player *player, float delta){
    move(&player, delta);
}