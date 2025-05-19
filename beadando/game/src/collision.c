#include "collision.h"
#include <stdio.h>
#include <stdbool.h>
#include "camera.h"
#include <string.h>

Col_vertex vertices[MAX_VERTICES];
int vertex_count = 0;
Object objects[MAX_OBJECTS];
int object_count = 0;

void load_obj(const char* filename){
    if (object_count >= MAX_OBJECTS) {
        printf("Max object reached..\n");
        return;
    }

    FILE* file = fopen(filename,"r");
    if(!file){
        printf("Open file error.: %s\n",filename);
        return;
    }

    Object* obj = &objects[object_count];
    obj->vertex_count = 0;

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            Col_vertex v;
            sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z);
            if (obj->vertex_count < MAX_VERTICES) {
                obj->vertices[obj->vertex_count++] = v;
            }
        }
    }

    fclose(file);
    object_count++;
}

void set_object_position(int index, float x, float y, float z) {
    if (index < object_count) {
        objects[index].pos_x = x;
        objects[index].pos_y = y;
        objects[index].pos_z = z;
    }
}

AABB get_obj(int index) {
    AABB obj;
    Object* o = &objects[index];

    obj.min_x = obj.min_y = obj.min_z = 10000.0;
    obj.max_x = obj.max_y = obj.max_z = -10000.0;

    for (int i = 0; i < o->vertex_count; ++i) {
        Col_vertex v = o->vertices[i];
        float x = v.x + o->pos_x;
        float y = v.y + o->pos_y;
        float z = v.z + o->pos_z;

        if (x < obj.min_x) obj.min_x = x;
        if (x > obj.max_x) obj.max_x = x;
        if (y < obj.min_y) obj.min_y = y;
        if (y > obj.max_y) obj.max_y = y;
        if (z < obj.min_z) obj.min_z = z;
        if (z > obj.max_z) obj.max_z = z;
    }

    return obj;
}


bool check_collision(Camera* camera,AABB obj){
    float cam_x = camera->position.x;
    float cam_y = camera->position.y;
    float cam_z = camera->position.z;

    return cam_x >= obj.min_x && cam_x <= obj.max_x &&
           cam_y >= obj.min_y && cam_y <= obj.max_y;

    /*return cam_x-1 >= obj.min_x && cam_x+1 <= obj.max_x &&
           cam_y-1 >= obj.min_y && cam_y+1 <= obj.max_y &&
           cam_z-1 >= obj.min_z && cam_z+1 <= obj.max_z;*/

}

int getObjCount(){
    return object_count;
}