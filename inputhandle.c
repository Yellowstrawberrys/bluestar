//
// Created by 정은수 on 2024. 6. 19.
//

#include "inputhandle.h"
#include "raylib.h"
#include "string.h"

void clearBuffer();


int coolTime = 0;
int buffI = 0;
char inputBuff[4];

void handleInput() {
    if(coolTime < 0) {
        clearBuffer();
    }else coolTime--;

    // TODO: Movements
    if(IsKeyDown(KEY_W)) {

    }else if(IsKeyDown(KEY_D)) {

    }else if(IsKeyDown(KEY_A)) {

    }else if(IsKeyDown(KEY_S)) {

    }

    char c = GetCharPressed();
    while (c!=0) {
        if(buffI<3&&(c=='i'||c=='j'||c=='k'||c=='l')) {inputBuff[buffI++] = c; coolTime = 60*3;}
        c = GetKeyPressed();
    }

    if(IsKeyDown(KEY_SPACE)) {
        if(strcasecmp(inputBuff, "IIKK")==0) {
            // TODO: Heal & -150 mana
        }else if(strcasecmp(inputBuff, "JJLL")==0) {
            // TODO: Damage with {mana} damage
        }else if(strcasecmp(inputBuff, "JLJL")==0) {
            // TODO: Normal Attack & -5 mana
        }else if(strcasecmp(inputBuff, "KLJK")==0) {
            // TODO: Arrange Damage & -70
        }else if(strcasecmp(inputBuff, "JILk")==0) {
            // TODO: Round Damage ~3m & -100
        }else {
            // TODO: 'Failed' Sound effect
        }
    }
}

void clearBuffer() {
    for(int i=0;i<4;i++) inputBuff[i] = '';
    buffI = 0;
}