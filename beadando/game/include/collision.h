#ifndef COLLISION_H
#define COLLISION_H


#include <stdbool.h>
#define MAX_VERTICES 10000
#define MAX_OBJECTS 100
#define CAMERA_SIZE 0.1f



int object_count;
typedef struct Camera Camera;
typedef struct Col_vertex{
    float x;
    float y;
    float z;
}Col_vertex;

typedef struct Object{
    Col_vertex vertices[MAX_VERTICES];
    int vertex_count;
    float pos_x;
    float pos_y;
    float pos_z;
} Object;

typedef struct AABB{
    float min_x, max_x;
    float min_y, max_y;
    float min_z, max_z;
} AABB;


AABB get_obj(int index);

void load_obj(const char* filename);

void set_object_position(int index, float x, float y, float z);

bool check_collision(Camera* camera, AABB obj);

int getObjCount();

#endif