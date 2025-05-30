#include "app.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "collision.h"
#include "enemy.h"

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;
    int screenWidth, screenHeight;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Metro!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        0, 0,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_GetWindowSize(app->window, &screenWidth, &screenHeight);

    init_opengl();
    reshape(screenWidth, screenHeight);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    load_obj("assets/models/wall.obj");

    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");
    load_obj("assets/models/pillar1.obj");

    set_object_position(1, -5.0f, -5.0f, 0.0f);
    set_object_position(2, 8.0f, 8.0f, 0.0f);
    set_object_position(3, 5.0f, 5.0f, 0.0f);
    set_object_position(4, -8.0f, -8.0f, 0.0f);
    set_object_position(5, -8.0f, 8.0f, 0.0f);
    set_object_position(6, -5.0f, 5.0f, 0.0f);
    set_object_position(7, 8.0f, -8.0f, 0.0f);
    set_object_position(8, 5.0f, -5.0f, 0.0f);

    load_obj("assets/models/raptor.obj");
    set_object_position(9, 10.0f, 10.0f, 0.0f);

    init_enemies();
    enemies[0].obj_index = 9;

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }
    else
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 100);
}

void running(App *app)
{
    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LSHIFT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
    {
        set_camera_speed(&(app->camera), 10);
    }
    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
    {
        set_camera_speed(&(app->camera), 4);
    }
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;
    int screenWidth, screenHeight;
    SDL_GetWindowSize(app->window, &screenWidth, &screenHeight);
    running(app);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -4);
                break;
            case SDL_SCANCODE_SPACE:
                set_camera_height(&(app->camera), 5.0);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 4);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -4);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_LSHIFT:
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (x <= 5 || x >= screenWidth - 5 || y <= 5 || y >= screenHeight - 5)
            {
                SDL_WarpMouseInWindow(app->window, screenWidth / 2, screenHeight / 2);
                mouse_x = screenWidth / 2;
                mouse_y = screenHeight / 2;
            }
            else
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
                mouse_x = x;
                mouse_y = y;
            }
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    // update_scene(&(app->scene));
    update_enemies(&(app->camera));
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene), &(app->camera));
    glPopMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
