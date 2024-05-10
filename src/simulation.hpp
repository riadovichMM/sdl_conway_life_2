#pragma once
#include <utility>
#include "./grid.hpp"

class Simulation {
    private:
        Grid* gird;
        Grid* tempGrid;
        std::pair<int, int> directions[8];
    public:
        Simulation(int width, int height, int cellSize, SDL_Renderer *pRenderer);
        void draw();
        void setCellValue(int row, int cell, int value);
        int countLiveNeighbors(int row, int cell);
        void updateStates();
};

