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

void initEnemy() {
    enemies = createList();
}

Enemy* spawnEnemy(const Vector2 vector2) {
    Enemy* enemy = (Enemy*) malloc(sizeof(Enemy)); // B - Enemy (1)
    Vector2* vec = malloc(sizeof(Vector2)); // B - Vector (1)
    vec->x = vector2.x;
    vec->y = vector2.y;
    Texture2D t = LoadTexture("../Assets/enemy/a.png");
    enemy->sprite = generateAnimatedSprite(&t, (Rectangle) {0,0,t.width/8, t.height}, vec, 8, 10); // B - AnimatedSprite (1)
    enemy->physics = generatePhysicsObject(vec, 10, 10, 10); // B - PhysicsObject (1)
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
    free(enemy->physics->pos); // R - Enemy (1)
    free(enemy->physics); // R - PhysicsObject (1)
    free(enemy->sprite->texture);
    free(enemy->sprite); // R - AnimatedSprite (1)
    free(enemy); // R - Enemy (1)
}

void destroyEnemies() {
    LNode* node = enemies->head;
    while (node) {
        Enemy* enemy = (Enemy*) node->address;
        free(enemy->physics->pos); // R - Enemy (1)
        free(enemy->physics); // R - PhysicsObject (1)
        free(enemy->sprite); // R - AnimatedSprite (1)
        free(enemy); // R - Enemy (1)
        node = node->next;
    }
    destroyList(enemies);
}