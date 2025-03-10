#include <stdio.h>
#include "line.h"

int main(){
    if(SDL_Init(SDL_INIT_VIDEO < 0)){
        printf("SDL error:  %s\n",SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Draw lines",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);

    if(!window){
        printf("Window error: %s\n",SDL_GetError());
        return 0;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Renderer error: %s\n",SDL_GetError());
        return 1;
    }
    bool running = true;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
            handleEvents(e);
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        draw(renderer);
        SDL_Delay(16);
        if(lineCount==CAPACITY){
            running = false;
            char message[50];
            sprintf(message, "You have reached the limit (%d).", CAPACITY);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Limit Reached",message, window); 
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}