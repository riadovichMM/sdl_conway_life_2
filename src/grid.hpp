#pragma once
#include "../include/SDL2/SDL.h"

class Grid {
    public:
        Grid(int width, int height, int cellSize, SDL_Renderer *pRenderer);
        void draw();
        void setValue(int row, int cell, int value);
        int getValue(int row, int cell);
        bool isWithinBounds(int row, int cell);
        int getRowsCount();
        int getCellsCount();
        void fillRandom();

    private:
        int rows;
        int cells;
        int cellSize;
        SDL_Renderer* pRenderer;
        int** matrix;
};
