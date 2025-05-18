#include <string.h>

#include "Grid.h"

void ResetGrid(Grid* grid) {
    memset(grid->cells, 0, sizeof(grid->cells));

    for (int cell = 0; cell < 81; cell++) {
        grid->candidates[cell] = 0b111111111;
    }
}

void SetCell(Grid* grid, int cell, int digit) {
    grid->cells[cell] = digit;
}

void ClearCell(Grid* grid, int cell) {
    U8 digit = grid->cells[cell];
    grid->cells[cell] = 0;
    AddCandidate(grid->candidates[cell], digit);
}