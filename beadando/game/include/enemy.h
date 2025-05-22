#ifndef ENEMY_H
#define ENEMY_H

#include "camera.h"
#include "collision.h"

typedef struct Enemy{
    float x, y, z;
    float speed;
    bool active;
    int obj_index;
    float respawn_x, respawn_y, respawn_z;
} Enemy;

#define MAX_ENEMIES 1
Enemy enemies[MAX_ENEMIES];
int enemy_count;

void init_enemies();
void update_enemies(Camera* camera);

#endif
