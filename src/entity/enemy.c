//
// Created by 정은수 on 2024. 6. 26..
//

#include "enemy.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utils/bsutils.h"
#include "player.h"
#include "raymath.h"

void destroyEnemy(Enemy* enemy);
void destroyBullet(Bullet* b);
void destroyBulletByPhysics(PhysicsObject* p);


List* enemies;
List* bullets;
Animation* aniEnemy;
Texture2D t;

void ab() {
    LNode* l = bullets->head;
    printf("-------\n");
    for(int i =0; i<bullets->size; i++) {
        printf("LNode: %p, pointing: %p\n", l, l->next);
        l = l->next;
    }
    printf("-------");
}

void initEnemy() {
    enemies = createList();
    bullets = createList();
    t = LoadTexture("../Assets/enemy/a.png");
    aniEnemy = generateAnimation(&t, (Rectangle) {0,0,t.width/8, t.height}, 8, 5, 1);
}

void onCollide(PhysicsObject* o, PhysicsObject* h) {
    if(h->type==0) {
        printf("c: %d\n", h->type);
        damagePlayer(10);
        destroyBulletByPhysics(o);
        ab();
    }
}

void spawnBullet(const Vector2 v, const Vector2 target) {
    Bullet* b = malloc(sizeof(Bullet));
    Vector2* vec = malloc(sizeof(Vector2));
    vec->x = v.x;
    vec->y = v.y;
    PhysicsObject* o = generatePhysicsObject(vec, 5, 5, 0.1f);
    o->force.x = (v.x-target.x) *0.1;
    o->force.y = (v.y-target.y) *0.1;
    o->onCollide = onCollide;
    o->type = 4;
    b->physics = o;
    addToList(bullets, b);
    ab();
}

void destroyBullet(Bullet* b) {
    printf("destroyed %p\n", b->physics);
    removeFromListByAddress(bullets, b);
    Vector2* v = b->physics->pos;
    unregisterPhysicsObject(b->physics);
    free(v);
    free(b);
}

void destroyBulletByPhysics(PhysicsObject* p) {
    const LNode* node = bullets->head;
    while (node) {
        if(((Bullet*)node->address)->physics == p) {
            destroyBullet(node->address);
            return;
        }
        node = node->next;
    }
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

void drawBullets() {
    const LNode* n = bullets->head;
    for (int i =0; i< bullets->size; i++) {
        PhysicsObject* o = ((Bullet*)n->address)->physics;
        DrawCircle(o->pos->x, o->pos->y, 5, YELLOW);
        if(((Bullet*)n->address)->age++>= 60) {destroyBulletByPhysics(o);}
        n = n->next;
    }
}

int tick = 0;

void tickEnemy() {

    // TODO
    LNode* node = enemies->head;
    while (node) {
        Enemy* e = (Enemy*)node->address;
        if(e->sprite->current == 5 && !tick) {
            spawnBullet(Vector2Add(*e->physics->pos, (Vector2) {0, 20}), *getPlayerPhysicsObject()->pos);
            tick = 1;
        }else tick = 0;

        node = node->next;
    }
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

    node = bullets->head;
    while (node) {
        destroyBullet(node->address);
        node = node->next;
    }
    destroyList(enemies);
    destroyList(bullets);
    destroyAnimation(aniEnemy);
    UnloadTexture(t);
}