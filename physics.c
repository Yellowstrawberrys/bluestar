//
// Created by 정은수 on 2024. 6. 13..
//
#include "bsutils.h"
#define GRAVITY 9.81

typedef struct _staticPhysicsObject {
    int id;
    float x,y,z,dx,dy,dz;
    int facing;
} StaticPhysicsObject;

typedef struct _physicsObject {
    int id;
    float x,y,z,dx,dy,dz;
    int facing;
    void (*onCollide)(struct _physicsObject*);

    float weight;
    float vx=0,vy=0,vz=0;
} PhysicsObject;

void update();
PhysicsObject* generatePhysicsObject();
StaticPhysicsObject* getStaticPhysicsObject();
void unregisterPhysicsObject(PhysicsObject* object);
void unregisterStaticPhysicsObject(StaticPhysicsObject* object);


List* physicsObjects = createList();
int* staticPhysicsObjects;

void update() {
    // LNode node = physicsObjects->head;
    // for(int i = 0; i < physicsObjects->size; i++) {
    //
    // }
}

PhysicsObject* generatePhysicsObject() {
    PhysicsObject physicsObject = {
    .id = 0,
    .x = 0,
    .y = 0,
    .z = 0,};
    return &physicsObject;
}
