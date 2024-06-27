//
// Created by 정은수 on 2024. 6. 26..
//

#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utils/bsutils.h"

void destroyEnemy(Enemy* enemy);


List* enemies;
int tickCounter;
Animation* aniEnemy;
Texture2D t;

void initEnemy() {
    enemies = createList();
    t = LoadTexture("../Assets/enemy/a.png");
    aniEnemy = generateAnimation(&t, (Rectangle) {0,0,t.width/8, t.height}, 8, 10, 1);
}

Enemy* spawnEnemy(const Vector2 vector2) {
    Enemy* enemy = (Enemy*) malloc(sizeof(Enemy)); // B - Enemy (1)
    Vector2* vec = malloc(sizeof(Vector2)); // B - Vector (1)
    vec->x = vector2.x;
    vec->y = vector2.y;
    enemy->sprite = generateAnimatedSprite(vec, 3); // B - AnimatedSprite (1)
    addToAList(enemy->sprite->animations, aniEnemy);
    enemy->sprite->type = 0;
    enemy->physics = generatePhysicsObject(vec, 65, 95, 50); // B - PhysicsObject (1)
    enemy->physics->type = 3;
    enemy->health = 50;
    addToList(enemies, enemy);
    return enemy;
}

void tickEnemy() {
    // TODO
    // srand(time(NULL));
    // LNode* node = enemies->head;
    // while (node) {
    //     int mv = rand()%3;
    //
    //
    //     if(tickCounter>120) {
    //         ((Enemy*)(node->address))
    //     }
    //
    //
    //     node = node->next;
    // }
    // tickCounter++;
}

void damageEnemy(const PhysicsObject* o, const int amount) {
    const LNode* node = enemies->head;
    while (node) {
        Enemy* enemy = (Enemy*) node->address;
        if(enemy->physics == o) {
            enemy->health -= amount;
            printf("health: %d\n", enemy->health);
            if(enemy->health <= 0) {
                destroyEnemy(enemy);
            }
            return;
        }
        node = node->next;
    }
}

void destroyEnemy(Enemy* enemy) {
    removeFromListByAddress(enemies, enemy);
    Vector2* vec = enemy->physics->pos;
    destroyAnimatedSprite(enemy->sprite); // R - AnimatedSprite (1)
    unregisterPhysicsObject(enemy->physics); // R - PhysicsObject (1)
    free(vec); // R - Vector (1)
    free(enemy); // R - Enemy (1)
}

void destroyEnemies() {
    const LNode* node = enemies->head;
    while (node) {
        Enemy* enemy = (Enemy*) node->address;
        Vector2* vec = enemy->physics->pos;
        unregisterPhysicsObject(enemy->physics); // R - PhysicsObject (1)
        destroyAnimatedSprite(enemy->sprite); // R - AnimatedSprite (1)
        free(vec); // R - Vector (1)
        free(enemy); // R - Enemy (1)
        node = node->next;
    }
    destroyList(enemies);
    destroyAnimation(aniEnemy);
    UnloadTexture(t);
}