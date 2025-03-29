#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->models[0]), "assets/models/floor.obj");
    scene->texture_ids[0] = load_texture("assets/textures/floor1.png");


    load_model(&(scene->models[1]), "assets/models/roof.obj");  
    scene->texture_ids[1] = load_texture("assets/textures/ceiling.png");

    load_model(&(scene->models[2]), "assets/models/pillar1.obj");  
    scene->texture_ids[2] = load_texture("assets/textures/floor1.png");

    load_model(&(scene->models[3]), "assets/models/wall.obj");  
    scene->texture_ids[3] = load_texture("assets/textures/floor1.png");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

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
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };
   

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{

}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    for (int i = 0; i < 4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, scene->texture_ids[i]);
        draw_model(&(scene->models[i]));
    }

    glPushMatrix();
    glTranslatef(-5.0f, -5.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0f, 8.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 5.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0f, -8.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0f, 8.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, 5.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0f, -8.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, -5.0f, 0.0f);
    draw_model(&(scene->models[2]));
    glPopMatrix();
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
