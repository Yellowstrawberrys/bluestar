//
// Created by 정은수 on 2024. 6. 26..
//

#include "audioman.h"
#include <raylib.h>

Sound audios[10];

void loadAudios() {
    audios[0] = LoadSound("../Assets/audio/failed.wav");
    audios[1] = LoadSound("../Assets/audio/magic.wav");
    audios[2] = LoadSound("../Assets/audio/magic2.wav");
    audios[3] = LoadSound("../Assets/audio/explosion.wav");
    audios[4] = LoadSound("../Assets/audio/manad.wav");
    audios[5] = LoadSound("../Assets/audio/heal.wav");
}

void playAudio(const int index) {
    PlaySound(audios[index]);
}

void unloadAudios() {
    for(int i = 0; i < sizeof(audios) / sizeof(Sound); i++) {
        UnloadSound(audios[i]);
    }
}