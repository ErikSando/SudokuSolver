#include <stdio.h>
#include <string.h>

#include "Assert.h"
#include "Bool.h"
#include "Grid.h"
#include "Utility.h"

const int NumberOfClues[6] = { 40, 35, 30, 25, 20, 17 };

void GetOccupiedCells(Grid* grid, int* cells) {
    int o_cells[82];
    int index = 0;

    for (int cell = 0; cell < 81; cell++) {
        if (grid->cells[cell]) {
            o_cells[index++] = cell;
        }
    }

    o_cells[81] = index;

    memcpy(cells, o_cells, sizeof(o_cells)); // sizeof(cells) won't work because its an integer
}

void ShuffleOccupiedCells(int* cells) {
    int length = cells[81];

    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int _ = cells[i];
        cells[i] = cells[j];
        cells[j] = _;
    }
}

void GeneratePuzzle(Grid* grid, const int difficulty) {
    Assert(difficulty >= 0 && difficulty <= (sizeof(NumberOfClues) / sizeof(const int)));
    
    const int clues = NumberOfClues[difficulty];

    // Fill the grid
    ResetGrid(grid);
    int _ = SolveGridRandomised(grid);
    Assert(_);

    // Remove digits while maitaining solvability until the desired number of clues is reached
    int o_cells[82];
    GetOccupiedCells(grid, o_cells);
    //ShuffleOccupiedCells(o_cells);

    int remaining = o_cells[81];
    int can_remove = remaining;

    while (remaining > clues && can_remove) {
        int index = rand() % can_remove;
        int cell = o_cells[index];

        for (int i = index; i < 80; i++) {
            o_cells[i] = o_cells[i + 1];
        }

        can_remove--;
        
        U8 digit = grid->cells[cell];
        ClearCell(grid, cell);

        if (NumberOfSolutions(grid) != 1) {
            SetCell(grid, cell, digit);
            continue;
        }

        remaining--;
        //PrintGrid(grid);
    }

    if (remaining > clues) {
        printf("Failed to generate puzzle\n");
        return;
    }

    PrintGrid(grid);
    printf("Puzzle generated with %d clues\n", clues);
}