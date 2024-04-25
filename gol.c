#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 100

int grid[ROWS][COLS];

void clearGrid() {
    int i, j;
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }
}

void initializeGrid() {
    int i, j;
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

void printGrid() {
    int i, j;
    system("clear");
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            if(grid[i][j] == 0)
                printf(".");
            else
                printf("*");
        }
        printf("\n");
    }
}

int countNeighbors(int x, int y) {
    int count = 0;
    int i, j;
    int neighborX, neighborY;
    for(i = -1; i <= 1; i++) {
        for(j = -1; j <= 1; j++) {
            neighborX = x + i;
            neighborY = y + j;
            if(neighborX >= 0 && neighborX < ROWS && neighborY >= 0 && neighborY < COLS) {
                count += grid[neighborX][neighborY];
            }
        }
    }
    count -= grid[x][y];
    return count;
}

void updateGrid() {
    int i, j;
    int neighbors;
    int newGrid[ROWS][COLS];
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            neighbors = countNeighbors(i, j);
            if(grid[i][j] == 1 && (neighbors < 2 || neighbors > 3)) {
                newGrid[i][j] = 0;
            } else if(grid[i][j] == 0 && neighbors == 3) {
                newGrid[i][j] = 1;
            } else {
                newGrid[i][j] = grid[i][j];
            }
        }
    }
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int main(int argc, char** argv) {
    clearGrid();
    initializeGrid();
    while(1) {
        printGrid();
        updateGrid();
        usleep(100000);
    }
    return 0;
}

