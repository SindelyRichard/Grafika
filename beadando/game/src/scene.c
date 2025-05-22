#include "scene.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>
#include "enemy.h"
#include "utils.h"

void init_scene(Scene *scene)
{
    load_model(&(scene->models[0]), "assets/models/floor.obj");
    scene->texture_ids[0] = load_texture("assets/textures/floor1.png");

    load_model(&(scene->models[1]), "assets/models/roof.obj");
    scene->texture_ids[1] = load_texture("assets/textures/ceiling.png");

    load_model(&(scene->models[2]), "assets/models/pillar1.obj");
    scene->texture_ids[2] = load_texture("assets/textures/pillar2.png");

    load_model(&(scene->models[3]), "assets/models/wall.obj");
    scene->texture_ids[3] = load_texture_rgb("assets/textures/wall4.png");

    load_model(&(scene->models[4]), "assets/models/raptor.obj");
    scene->texture_ids[4] = load_texture("assets/textures/raptor.png");

    scene->material.ambient.red = 0.3;
    scene->material.ambient.green = 0.3;
    scene->material.ambient.blue = 0.3;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = {1.0f, 1.0f, 1.0f, 0.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float position[] = {7.0f, 7.0f, 9.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void shadow_matrix(GLfloat shadowMat[16], GLfloat lightPos[4], GLfloat plane[4])
{
    float dot = plane[0] * lightPos[0] +
                plane[1] * lightPos[1] +
                plane[2] * lightPos[2] +
                plane[3] * lightPos[3];

    shadowMat[0] = dot - lightPos[0] * plane[0];
    shadowMat[4] = 0.0f - lightPos[0] * plane[1];
    shadowMat[8] = 0.0f - lightPos[0] * plane[2];
    shadowMat[12] = 0.0f - lightPos[0] * plane[3];

    shadowMat[1] = 0.0f - lightPos[1] * plane[0];
    shadowMat[5] = dot - lightPos[1] * plane[1];
    shadowMat[9] = 0.0f - lightPos[1] * plane[2];
    shadowMat[13] = 0.0f - lightPos[1] * plane[3];

    shadowMat[2] = 0.0f - lightPos[2] * plane[0];
    shadowMat[6] = 0.0f - lightPos[2] * plane[1];
    shadowMat[10] = dot - lightPos[2] * plane[2];
    shadowMat[14] = 0.0f - lightPos[2] * plane[3];

    shadowMat[3] = 0.0f - lightPos[3] * plane[0];
    shadowMat[7] = 0.0f - lightPos[3] * plane[1];
    shadowMat[11] = 0.0f - lightPos[3] * plane[2];
    shadowMat[15] = dot - lightPos[3] * plane[3];
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}
/*
void update_scene(Scene *scene)
{
}
*/

void render_scene(const Scene *scene, const Camera *camera)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    for (int i = 0; i < 4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, scene->texture_ids[i]);
        draw_model(&(scene->models[i]));
    }
    float dx = camera->position.x - enemies[0].x;
    float dy = camera->position.y - enemies[0].y;
    float angle = atan2f(dy, dx) * 180.0f / M_PI - 90.0f;

    glPushMatrix();
    glTranslatef(enemies[0].x, enemies[0].y, enemies[0].z);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[4]);
    draw_model(&(scene->models[4]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, -5.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0f, 8.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 5.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0f, -8.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0f, 8.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 5.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0f, -8.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, -5.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_ids[2]);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    GLfloat shadowMat[16];
    GLfloat lightPos[] = {0.0f, 0.0f, 10.0f, 1.0f};
    GLfloat floorPlane[] = {0.0f, 0.0f, 1.0f, 0.0f};

    shadow_matrix(shadowMat, lightPos, floorPlane);

    glDisable(GL_LIGHTING);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);

    glPushMatrix();
    glMultMatrixf(shadowMat);
    glTranslatef(enemies[0].x, enemies[0].y, 0.1f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    draw_model(&(scene->models[4]));
    glPopMatrix();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHTING);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);

    const float pillar_positions[][2] = {
        {-5.0f, -5.0f},
        {8.0f, 8.0f},
        {5.0f, 5.0f},
        {-8.0f, -8.0f},
        {-8.0f, 8.0f},
        {-5.0f, 5.0f},
        {8.0f, -8.0f},
        {5.0f, -5.0f}};

    for (int i = 0; i < 8; ++i)
    {
        float x = pillar_positions[i][0];
        float y = pillar_positions[i][1];

        glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(x, y, 0.1f);
        draw_model(&(scene->models[2]));
        glPopMatrix();
    }

    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_LIGHTING);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
