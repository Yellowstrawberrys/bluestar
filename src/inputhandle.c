//
// Created by 정은수 on 2024. 6. 19.
//

#include "inputhandle.h"

#include <stdio.h>

#include "audioman.h"
#include "raylib.h"
#include "string.h"
#include "entity/player.h"
#include "entity/player.h"

void clearBuffer();


int coolTime = 0;
int buffI = 0;
char inputBuff[5];

void handleInput(Player* player) { //adding player struct and deltatime
    if(coolTime < 0) {
        clearBuffer();
    }else coolTime--;

    if(IsKeyPressed(KEY_W)) {
        jumpPlayer(player);
    }else if(IsKeyDown(KEY_D)) {
        movePlayer(1, player);
    }else if(IsKeyDown(KEY_A)) {
        movePlayer(-1, player);
    }

    char c = GetCharPressed();
    while (c!=0) {
        if(buffI<4&&(c=='i'||c=='j'||c=='k'||c=='l')) {inputBuff[buffI++] = c; coolTime = 60*3;}
        c = GetKeyPressed();
    }

    if(IsKeyPressed(KEY_SPACE)) {
        printf("%s\n", inputBuff);
        if(strcasecmp(inputBuff, "IIKK")==0 && useMana(150, player)) {
            heal(50, player);
            playAudio(5);
        }else if(strcasecmp(inputBuff, "JJLL")==0) {
            // TODO: Damage with {mana} damage
        }else if(strcasecmp(inputBuff, "JLJL")==0&&useMana(5, player)) {
            shootMagic(0, *player);
            playAudio(1);
        }else if(strcasecmp(inputBuff, "KLJK")==0 && useMana(70, player)) {
            shootMagic(1, *player);
            playAudio(2);
        }else if(strcasecmp(inputBuff, "JILk")==0) {
            // TODO: Round Damage ~3m & -100
        }else {
            playAudio(0);
        }
        clearBuffer();
    }
}

int isInputBuffEmpty() {
    return buffI == 0;
}

char* getInputBuff() {
    return inputBuff;
}

void clearBuffer() {
    for(int i=0;i<4;i++) inputBuff[i] = '\0';
    buffI = 0;
}