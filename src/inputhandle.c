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

void handleInput() { //adding player struct and deltatime
    if(coolTime < 0) {
        clearBuffer();
    }else coolTime--;

    if(IsKeyPressed(KEY_W)) {
        jumpPlayer();
    }else if(IsKeyDown(KEY_D)) {
        movePlayer(1);
    }else if(IsKeyDown(KEY_A)) {
        movePlayer(-1);
    }

    char c = GetCharPressed();
    while (c!=0) {
        if(buffI<4&&(c=='i'||c=='j'||c=='k'||c=='l')) {inputBuff[buffI++] = c; coolTime = 60*3;}
        c = GetKeyPressed();
    }

    if(IsKeyPressed(KEY_SPACE)) {
        printf("%s\n", inputBuff);
        if(strcasecmp(inputBuff, "IIKK")==0 && useMana(150)) {
            heal(50);
            playAudio(5);
        }else if(strcasecmp(inputBuff, "JJLL")==0) {
            // TODO: Damage with {mana} damage
        }else if(strcasecmp(inputBuff, "JLJL")==0&&useMana(5)) {
            shootMagic(0);
            playAudio(1);
        }else if(strcasecmp(inputBuff, "KLJK")==0 && useMana(70)) {
            shootMagic(1);
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