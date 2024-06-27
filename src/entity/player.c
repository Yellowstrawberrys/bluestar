#include "raylib.h"
#include "player.h"
#include <math.h>

#include "magic.h"
#include "../animation.h"
#include "../physics.h"
#include "../utils/bsutils.h"
#include "../cameraman.h"

bool iscolliding = false;

Texture2D texture[2];
Player* player;

int health = PLAYER_MAX_HP, mana = PLAYER_MAX_MANA;
int canJump = 1, f=0, mt=-1, fm=0;

void tickPlayer() {
    if(mana>=PLAYER_MAX_MANA) return;
    f++;
    if(f>40) {mana++;f=0;}
    if(mt != -1) fm++;
    if(fm>13 && mt != -1) {
        switch (mt) {
            case 0:
                spawnMagic((Vector2) {player->pos.x+35*player->physics->facing, player->pos.y - player->physics->height}, 10*player->physics->facing)->physics->type=1;
            break;
            case 1:
                spawnMagic((Vector2) {player->pos.x+35*player->physics->facing, player->pos.y - player->physics->height}, 10*player->physics->facing)->physics->type=2;
            break;
            default: break;
        }
        mt = -1;
        fm = 0;
    }
}

void onPhysicsUpdate(Vector2 changed) {
    if(player->sprite->type == 0 && fabsf(changed.x) > 0) {
        player->sprite->pause = 0;
    }else if(player->sprite->type == 0) {
        player->sprite->pause = 1;
    }

    if(player->pos.y >= 300) canJump = 1;
}

void initPlayer(Player* p) {
    printf("initPlayer called\n");
    texture[0] = LoadTexture("../Assets/character/walk.png");
    texture[1] = LoadTexture("../Assets/character/magic.png");
    player = p;
    player->pos.x = 350.0f;
    player->pos.y = 200.0f;
    player->health = PLAYER_MAX_HP;
    player->mana = PLAYER_MAX_MANA;
    player->f = 0;
    player->canJump = 1;
    player->sprite = generateAnimatedSprite(&player->pos, 2);
    addToAList(player->sprite->animations, generateAnimation(&texture[0], (Rectangle) {0, 0, texture[0].width/4, texture[0].height}, 4, 7, 1));
    addToAList(player->sprite->animations, generateAnimationWithOffset(&texture[1], (Rectangle) {0, 0, texture[1].width/5, texture[1].height}, 5, 10, (Vector2) {23, 0}, 0));
    player->sprite->type = 0;
    player->sprite->pause = 1;
    printf("initPlayer called9%lu\n",sizeof(PhysicsObject));
    player->physics = generatePhysicsObject(&player->pos, 20, 40, 10);
    player->physics->onPhysicsUpdate = onPhysicsUpdate;
    printf("Player initialized successfully\n");
}

PhysicsObject* getPlayerPhysicsObject() {
    return player->physics;
}

AnimatedSprite* getPlayerSprite() {
    printf("getPlayerSprite called\n");
    return player->sprite;
}

void heal(const int i) {
    printf("heal called with healed HP : %d\n", i);
    player->health = imin(100, player->health+i);
}

int useMana(const int i) {
    printf("useMana called with used mana : %d\n", i);
    if(player->mana-i >= 0 ) {
        player->mana -= i;
        return 1;
    }
    return 0;
}

int getPlayerHealth() {
    printf("getPlayerHealth called\n");
    return player->health;
}

int getPlayerMana() {
    printf("getPlayerMana called\n");
    return player->mana;
}

void jumpPlayer() {
    printf("jumping called. CanJump: %d\n", player->canJump);
    if(!player->canJump) return;
    player->physics->force.y -= PLAYER_JUMP_F;
    player->canJump = 0;
}


void shootMagic(const int type) {
    addCameraOffset( (Vector2) {5*player->physics->facing, 0});
    player->sprite->type = 1;
    player->sprite->current = 0;
    player->sprite->pause = 0;
    mt = type;
}

void movePlayer(const int modifier) {
    player->physics->facing = modifier;
    player->sprite->flipMod = modifier;
    if(fabsf(player->physics->force.x) < PLAYER_MAX_SPEED) player->physics->force.x += 2*modifier;
}

void destroyPlayer() {
    UnloadTexture(texture[0]);
    UnloadTexture(texture[1]);
    destroyAnimatedSprite(player->sprite);
}

int checkPlayerTileCollision(Player* player, Rectangle collisionBoxes, Rectangle playerRect) {
    if(CheckCollisionRecs(playerRect, collisionBoxes)) {
        printf("col\n");
        iscolliding = true;
    }
    return 0;
}