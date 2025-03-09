#include "line.h"

Line lines[CAPACITY];
int lineCount = 0;
bool waitingForSecondPoint = false;

SDL_Color randomColor(){
    SDL_Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    color.a = 255;
    return color;
}

void handleEvents(SDL_Event e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int x = e.button.x;
        int y = e.button.y;
        if(lineCount < CAPACITY){
            if(!waitingForSecondPoint){
                lines[lineCount] = (Line){randomColor(),{x,y},{0,0}};
                waitingForSecondPoint = true;
            }else{
                lines[lineCount].end.x = x;
                lines[lineCount].end.y = y;
                lineCount++;
                waitingForSecondPoint = false;
            }
        }
    }
}

void draw(SDL_Renderer *renderer){
    for (int i = 0; i < lineCount; i++)
    {
        SDL_SetRenderDrawColor(renderer,lines[i].color.r,lines[i].color.g,lines[i].color.b,lines[i].color.a);
        SDL_RenderDrawLine(renderer,lines[i].start.x,lines[i].start.y,lines[i].end.x,lines[i].end.y);
    }
    SDL_RenderPresent(renderer);
}