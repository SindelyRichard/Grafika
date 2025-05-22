#include "enemy.h"
#include <math.h>
#include <stdio.h>

Enemy enemies[MAX_ENEMIES];
int enemy_count = 0;

void init_enemies()
{
    Enemy *e = &enemies[enemy_count++];
    e->x = 10.0f;
    e->y = 10.0f;
    e->z = 0.0f;
    e->respawn_x = e->x;
    e->respawn_y = e->y;
    e->respawn_z = e->z;
    e->speed = 0.03f;
    e->active = true;
    e->obj_index = 5;
}

void update_enemies(Camera *camera)
{
    for (int i = 0; i < enemy_count; ++i)
    {
        Enemy *e = &enemies[i];
        if (!e->active)
            continue;

        float dx = camera->position.x - e->x;
        float dy = camera->position.y - e->y;
        //float dz = camera->position.z - e->z;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist < 1.0f)
        {
            printf("MEGHALTÁL!\n");
            camera->position.x = 10.0;
            camera->position.y = 0.0;
            camera->position.z = 1.0;

            camera->rotation.x = 0.0;
            camera->rotation.y = 0.0;
            camera->rotation.z = 90.0;

            e->x = e->respawn_x;
            e->y = e->respawn_y;
            e->z = e->respawn_z;
            continue;
        }

        if (dist > 0.01f)
        {
            float dir_x = dx / dist;
            float dir_y = dy / dist;
            float next_x = e->x + dir_x * e->speed;
            float next_y = e->y + dir_y * e->speed;

            if (check_collision_enemy(next_x, next_y, e->z))
            {
                float right_x = -dir_y;
                float right_y = dir_x;
                e->x += right_x * e->speed;
                e->y += right_y * e->speed;
            }
            else
            {
                e->x = next_x;
                e->y = next_y;
            }
        }
    }
}