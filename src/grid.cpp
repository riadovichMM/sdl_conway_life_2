#include <iostream>
#include <random>
#include "./grid.hpp"
#include "../include/SDL2/SDL.h"


std::random_device rd;
std::mt19937 gen(rd());
std::bernoulli_distribution dis(0.5); // генерация случайного бита с вероятностью 0.5


Grid::Grid(int width, int height, int cellSize, SDL_Renderer *pRenderer) {
    (*this).rows = height / cellSize;
    (*this).cells = width / cellSize;
    (*this).cellSize = cellSize;

    (*this).matrix = new int*[(*this).rows];

    for (int i = 0; i < (*this).rows; i++) {
        (*this).matrix[i] = new int[(*this).cells];
    }

    for (int i = 0; i < (*this).rows; i++) {
        for (int j = 0; j < (*this).cells; j++) {
            (*this).matrix[i][j] = 0;
        }
    }

    (*this).pRenderer = pRenderer;
}


void Grid::draw() {

    //display to terminal
    // for (int i = 0; i < (*this).rows; i++) {
    //     for (int j = 0; j < (*this).cells; j++) {
    //         std::cout << (*this).matrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }


    for (int i = 0; i < (*this).rows; i++) {
        for (int j = 0; j < (*this).cells; j++) {

            if ((*this).matrix[i][j] == 1) {
                SDL_Rect rect;

                rect.h = (*this).cellSize - 1;
                rect.w = (*this).cellSize - 1;

                rect.x = j * (*this).cellSize;
                rect.y = i * (*this).cellSize;

                SDL_RenderFillRect(pRenderer, &rect);
            }

        }
    }

}

void Grid::setValue(int row, int cell, int value) {
    if(this->isWithinBounds(row, cell)){
        (*this).matrix[row][cell] = value;
    }
}

int Grid::getValue(int row, int cell) {
    if(this->isWithinBounds(row, cell)){
        return this->matrix[row][cell];
    }
    return 0;
}

bool Grid::isWithinBounds(int row, int cell) {
    if (row >= 0 && row < this->rows && cell >= 0 && cell < this->cells) {
        return true;
    }
    return false;
}

int Grid::getRowsCount() {
    return this->rows;
}


int Grid::getCellsCount() {
    return this->cells;
}

void Grid::fillRandom() {
    for(int row = 0; row < this->rows; row++) {
        for (int cell = 0; cell < this->cells; cell++) {
            int random_number = dis(gen);
            this->matrix[row][cell] = random_number;
        }
    }
}