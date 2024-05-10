#include <iostream>
#include "./simulation.hpp"
#include "./grid.hpp"

Simulation::Simulation(int width, int height, int cellSize, SDL_Renderer *pRenderer) {
    (*this).gird = new Grid(width, height, cellSize, pRenderer);
    (*(*this).gird).fillRandom();
    (*this).tempGrid = new Grid(width, height, cellSize, pRenderer);


    (*this).directions[0] = {-1, -1};
    (*this).directions[1] = {-1, 0};
    (*this).directions[2] = {-1, 1};
    (*this).directions[3] = {0, -1};
    (*this).directions[4] = {0, 1};
    (*this).directions[5] = {1, -1};
    (*this).directions[6] = {1, 0};
    (*this).directions[7] = {1, 1};

}


void Simulation::draw() {
    (*(*this).gird).draw();
}

void Simulation::setCellValue(int row, int cell, int value) {
    (*(*this).gird).setValue(row, cell, value);
}


int Simulation::countLiveNeighbors(int row, int cell) {
    int acc = 0;
    for(int i = 0; i < 8; i++) {
        int nRow = (row + this->directions[i].first + this->gird->getRowsCount()) % this->gird->getRowsCount();
        int nCell = (cell + this->directions[i].second + this->gird->getCellsCount()) % this->gird->getCellsCount();
        
        acc = acc + this->gird->getValue(nRow, nCell);
    } 
    return acc;
}

void Simulation::updateStates() {
    for (int row = 0; row < this->gird->getRowsCount(); row++) {
        for (int cell = 0; cell < this->gird->getCellsCount(); cell++) {
            int liveNeighbors = this->countLiveNeighbors(row, cell);
            int cellValue = this->gird->getValue(row, cell);

            if (cellValue == 1) {
                if (liveNeighbors > 3 || liveNeighbors < 2) {
                    tempGrid->setValue(row, cell, 0);
                } else {
                    tempGrid->setValue(row, cell, 1);
                }
            } else {
                if (liveNeighbors == 3) {
                    tempGrid->setValue(row, cell, 1);
                } else {
                    tempGrid->setValue(row, cell, 0);
                }
            }
        }
    }

    Grid* gridPtr;
    gridPtr = this->gird;
    this->gird = this->tempGrid;
    this->tempGrid = gridPtr;
    gridPtr = nullptr;
}