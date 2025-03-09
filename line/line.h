#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAPACITY 6

typedef struct Line{
    SDL_Color color;
    SDL_Point start;
    SDL_Point end;
}Line;

SDL_Color randomColor();
void handleEvents(SDL_Event e);
void draw(SDL_Renderer *renderer);

extern Line lines[CAPACITY];
extern int lineCount;
extern bool waitingForSecondPoint;

#endif