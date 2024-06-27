//
// Created by 정은수 on 2024. 6. 26..
//

#ifndef ENEMY_H
#define ENEMY_H
#include "../animation.h"
#include "../physics.h"

typedef struct _enemy {
    AnimatedSprite* sprite;
    PhysicsObject* physics;
    int health;
} Enemy;

void initEnemy();
Enemy* spawnEnemy(const Vector2 vector2);
void damageEnemy(const PhysicsObject* o, const int amount);
void destroyEnemies();

#endif //ENEMY_H
