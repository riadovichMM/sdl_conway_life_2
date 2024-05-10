#include <iostream>
#include "../include/SDL2/SDL.h"
#include "./grid.hpp"
#include "./simulation.hpp"


int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int CELL_SIZE;



int main() {
    std::cout << "width of screen:" << std::endl;
    std::cin >> WINDOW_WIDTH;

    std::cout << "height of screen:" << std::endl;
    std::cin >> WINDOW_HEIGHT;

    std::cout << "cell size" << std::endl;
    std::cin >> CELL_SIZE;


    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "sdl error" << std::endl;
        return 1;
    }

    SDL_Window* pWindow = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);


    if (pWindow == NULL) {
        std::cout << "create window error" << std::endl;
        return 1;
    }

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    if (pRenderer == NULL) {
        std::cout << "renderer error" << std::endl;
        return 1;
    }

    Simulation sim(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE, pRenderer);
    sim.setCellValue(1,1,1);
    sim.setCellValue(1,2,1);
    sim.setCellValue(1,0,1);

    std::cout << sim.countLiveNeighbors(1,1) << std::endl;


    bool run = true;
    SDL_Event e;

    while(run) {

        // event handling
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
        }

        // update states
        sim.updateStates();


        //render
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
        SDL_RenderClear(pRenderer);

        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);
        sim.draw();


        SDL_RenderPresent(pRenderer);
    }


    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    SDL_Quit();

    pWindow = nullptr;
    pRenderer = nullptr;


    return 0;
}