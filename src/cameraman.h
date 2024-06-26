//
// Created by 정은수 on 2024. 6. 26..
//

#ifndef CAMERAMAN_H
#define CAMERAMAN_H
#include "physics.h"
#include "raylib.h"

Camera2D* initCamera();
void updateCamera(const PhysicsObject* target);
void addCameraOffset(const Vector2 vec);

#endif //CAMERAMAN_H
