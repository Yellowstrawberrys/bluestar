//
// Created by 정은수 on 2024. 6. 26..
//

#ifndef AUDIOMAN_H
#define AUDIOMAN_H

#include "raylib.h"

extern Sound audios[10];  // extern으로 선언

void loadAudios();
void playAudio(int index);
void unloadAudios();

#endif //AUDIOMAN_H
