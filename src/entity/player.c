#include "player.h"

bool iscolliding = false;

void tickPlayer(Player* player) {
    if(player->mana>=PLAYER_MAX_MANA) return;
    player->f++;
    if(player->f>40) {player->mana++;player->f=0;}
}

void onPhysicsUpdate(Vector2 changed, Player* player) {
    printf("onPhysicsUpdate called with changed.x: %f, player->pos.y: %f\n", changed.x, player->pos.y);
    if (fabsf(changed.x) > 0) {
        if(fabsf(changed.x) > 0) {
            player->sprite->pause = 0;
        }else {
            player->sprite->current = 0;
            player->sprite->pause = 1;
        }

        if(player->pos.y >= 300) player->canJump = 1;
    }
}

void initPlayer(Texture2D* scarfy, Player* player) {
    printf("initPlayer called\n");
    player->pos.x = 350.0f;
    player->pos.y = 200.0f;
    player->health = PLAYER_MAX_HP;
    player->mana = PLAYER_MAX_MANA;
    player->f = 0;
    player->canJump = 1;
    player->sprite = generateAnimatedSprite(scarfy, (Rectangle) {0, 0, (float)scarfy->width/6, (float)scarfy->height}, &player->pos, 6, 20);
    player->sprite->pause = 1;
    printf("initPlayer called9%lu\n",sizeof(PhysicsObject));
    player->physics = generatePhysicsObject(&player->pos, 50, 60, 10);
    player->physics->onPhysicsUpdate = onPhysicsUpdate;
    printf("Player initialized successfully\n");
}

PhysicsObject* getPlayerPhysicsObject(Player player) {
    return player.physics;
}

AnimatedSprite* getPlayerSprite(Player player) {
    printf("getPlayerSprite called\n");
    return player.sprite;
}

void heal(const int i, Player* player) {
    printf("heal called with healed HP : %d\n", i);
    player->health = imin(100, player->health+i);
}

int useMana(const int i, Player* player) {
    printf("useMana called with used mana : %d\n", i);
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

void jumpPlayer(Player* player) {
    printf("jumping called. CanJump: %d\n", player->canJump);
    if(!player->canJump) return;
    player->physics->force.y -= PLAYER_JUMP_F;
    player->canJump = 0;
}


void shootMagic(const int type, Player player) {
    printf("Attack called with type: %d\n", type);
    addCameraOffset( (Vector2) {5 * player.physics->facing, 0});
    switch (type) {
        case 0:
            spawnMagic(player.pos, 10 * player.physics->facing)->physics->type=1;
            break;
        case 1:
            spawnMagic(player.pos, 10 * player.physics->facing)->physics->type=2;
            break;
        default: break;
    }
}

void movePlayer(const int modifier, Player* player) {
    player->physics->facing = modifier;
    player->sprite->flipMod = modifier;
    if(fabsf(player->physics->force.x) < PLAYER_MAX_SPEED) player->physics->force.x += 2*modifier;
}

void destroyPlayer(Player* player) {
    printf("destroyPlayer called\n");
    destroyAnimatedSprite(player->sprite);
}

int checkPlayerTileCollision(Player* player, Rectangle collisionBoxes, Rectangle playerRect) {
    if(CheckCollisionRecs(playerRect, collisionBoxes)) {
        printf("col\n");
        iscolliding = true;
    }
    return 0;
}