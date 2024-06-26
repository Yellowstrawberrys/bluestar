//
// Created by 정은수 on 2024. 6. 26..
//

#include "cameraman.h"

#include <math.h>
#include <stdio.h>

#include "physics.h"
#include "raylib.h"

#define CAMERA_OFFSET_X (1920/2/2.0f)
#define CAMERA_OFFSET_Y (1080/2/2.0f)

#define CAMERA_OFFSET_F .1f

Camera2D camera = { 0 };
Vector2 force = {0, 0};
int shakeMode = 0;

Camera2D* initCamera() {
    camera.offset = (Vector2) {CAMERA_OFFSET_X, CAMERA_OFFSET_Y};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return &camera;
}

void updateCamera(const PhysicsObject* target) {
    camera.target = *target->pos;

    if(camera.offset.x != CAMERA_OFFSET_X) {
        if(round(camera.offset.x) == CAMERA_OFFSET_X) {camera.offset.x = CAMERA_OFFSET_X;force.x=0;return;}
        force.x += (CAMERA_OFFSET_X-fabsf(camera.offset.x))*CAMERA_OFFSET_F;
    }
    camera.offset.x += force.x;
    camera.offset.y += force.y;
    if(force.x != 0) force.x -= force.x/fabsf(force.x)*(shakeMode?CAMERA_OFFSET_F:1);
}

void addCameraOffset(const Vector2 vec) {
    force.x += vec.x;
    force.y += vec.y;
}