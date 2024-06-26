#include "raylib.h"
#include "player.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "magic.h"
#include "../animation.h"
#include "../physics.h"
#include "../utils/bsutils.h"

void tickPlayer(Player* player) {
    if(player->mana>=PLAYER_MAX_MANA) return;
    player->f++;
    if(player->f>40) {player->mana++; player->f=0;}
    printf("tickPlayer called. Mana: %d\n", player->mana);
}

void onPhysicsUpdate(Vector2 changed, Player* player) {
    if(fabsf(changed.x) > 0) {
        player->sprite->pause = 0;
    }else {
        player->sprite->current = 0;
        player->sprite->pause = 1;
    }

    if(player->pos.y >= 300) player->canJump = 1;
    printf("onPhysicsUpdate called with changed.x: %f, player->pos.y: %f\n", changed.x, player->pos.y);
}

<<<<<<< Updated upstream
void initPlayer(Texture2D* scarfy) {
    frameRec = malloc(sizeof(frameRec)); // B 1
    frameRec->width = (float)scarfy->width/6;
    frameRec->height = (float)scarfy->height;
    sprite = generateAnimatedSprite(scarfy, frameRec, &pos, 6, 20);
    sprite->pause = 1;
    physics = generatePhysicsObject(&pos, 50, 60, 10);
    physics->onPhysicsUpdate = &onPhysicsUpdate;
=======
void initPlayer(Texture2D* scarfy, Player* player) {
    printf("initializing Player...\n");
    player->pos.x = 350.0f;
    player->pos.y = 200.0f;
    player->f = 0;
    player->canJump = 1;
    player->health = PLAYER_MAX_HP;
    player->mana = PLAYER_MAX_MANA;
    player->sprite = generateAnimatedSprite(scarfy, (Rectangle) {0, 0, (float)scarfy->width / 6, (float)scarfy->height}, &player->pos, 6, 20);
    if (player->sprite == NULL) {
        printf("Error initializing sprite\n");
        exit(1);
    }
    player->sprite->pause = 1;
    player->physics = generatePhysicsObject(&player->pos, 50, 60, 10);
    if (player->physics == NULL) {
        printf("Error initializing physics\n");
        exit(1);
    }
    player->physics->onPhysicsUpdate = onPhysicsUpdate;
    printf("Player initialized successfully\n");
} //No problems

PhysicsObject* getPlayerPhysicsObject(Player player) {
    printf("getPlayerPhysicsObject called\n");
    return player.physics;
>>>>>>> Stashed changes
}

AnimatedSprite* getPlayerSprite(Player player) {
    printf("getPlayerSprite called\n");
    return player.sprite;
}

void heal(const int i, Player* player) {
    printf("heal called with i: %d\n", i);
    player->health = imin(100, player->health+i);
}

int useMana(const int i, Player* player) {
    printf("useMana called with i: %d\n", i);
    if(player->mana-i >= 0 ) {
        player->mana -= i;
        return 1;
    }
    return 0;
}

int getPlayerHealth(Player player) {
    printf("getPlayerHealth called\n");
    return player.health;
}

int getPlayerMana(Player player) {
    printf("getPlayerMana called\n");
    return player.mana;
}

<<<<<<< Updated upstream
void jumpPlayer() {
    if(!canJump) return;
    printf("%f\n", pos.y);
    physics->force.y -= PLAYER_JUMP_F;
    canJump = 0;
}


void shootMagic(const int type) {
=======
void jumpPlayer(Player* player) {
    printf("jumpPlayer called. CanJump: %d\n", player->canJump);
    if(!player->canJump) return;
    player->physics->force.y -= PLAYER_JUMP_F;
    player->canJump = 0;
}


void shootMagic(const int type, Player player) {
    printf("shootMagic called with type: %d\n", type);
    addCameraOffset( (Vector2) {5 * player.physics->facing, 0});
>>>>>>> Stashed changes
    switch (type) {
        case 0:
            spawnMagic(player.pos, 10 * player.physics->facing)->physics->type=1;
            break;
<<<<<<< Updated upstream
=======
        case 1:
            spawnMagic(player.pos, 10 * player.physics->facing)->physics->type=2;
            break;
>>>>>>> Stashed changes
        default: break;
    }
}

void movePlayer(const int modifier, Player* player) {
    printf("movePlayer called with modifier: %d\n", modifier);
    player->physics->facing = modifier;
    player->sprite->flipMod = modifier;
    if(fabsf(player->physics->force.x) < PLAYER_MAX_SPEED) player->physics->force.x += 2*modifier;
}

<<<<<<< Updated upstream
void destroyPlayer() {
    destroyAnimatedSprite(sprite);
    free(frameRec); // R 1
=======
void destroyPlayer(Player* player) {
    printf("destroyPlayer called\n");
    destroyAnimatedSprite(player->sprite);
>>>>>>> Stashed changes
}