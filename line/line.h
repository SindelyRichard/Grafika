#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAPACITY 3

typedef struct Line{
    SDL_Color color;
    SDL_Point start;
    SDL_Point end;
}Line;

SDL_Color randomColor();
void handleEvents(SDL_Event e,int* lineCount);
void draw(SDL_Renderer *renderer,int lineCount);

#endif