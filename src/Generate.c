#include <stdio.h>
#include <string.h>

#include "Assert.h"
#include "Bool.h"
#include "Grid.h"
#include "Utility.h"

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

void GeneratePuzzle(Grid* grid, const int clues, const int attempts) {
    Assert(clues >= 17 && clues <= 81);

    printf("Maximum attempts: %d\n", attempts);
    printf("Attempting to generate puzzle with %d clues...\n", clues);

    //Grid* grids[attempts];

    Grid* grids = (Grid*) malloc(attempts * sizeof(Grid));



    int best = 81;
    Grid* best_grid = &grids[0];

    for (int a = 0; a < attempts; a++) {
        Grid* g = &grids[a];

        // Fill the grid
        InitGrid(g);
        ResetGrid(g);
        int _ = SolveGridRandomised(g);
        Assert(_);

        // Remove digits while maitaining solvability until the desired number of clues is reached
        int o_cells[82];
        // i realised that every cell should be occupied at this point, so i dont really need this
        GetOccupiedCells(g, o_cells);
        ShuffleOccupiedCells(o_cells);

        int remaining = 81;

        for (int i = 0; i < 81; i++) {
            if (remaining <= clues) break;

            int cell = o_cells[i];

            U8 digit = g->cells[cell];
            ClearCell(g, cell);

            if (NumberOfSolutions(g) != 1) {
                SetCell(g, cell, digit);
                continue;
            }

            remaining--;
        }

        if (remaining > clues) {
            printf("Failed attempt %d, achieved %d clues\n", a + 1, remaining);
        }

        if (remaining < best) {
            best = remaining;
            best_grid = g;

            if (best <= clues) break;
        }
    }

    CopyGrid(best_grid, grid);

    free(grids);

    if (best > clues) {
        printf("Failed to reach %d clues, best achieved: %d\n", clues, best);
        PrintGrid(grid);
        return;
    }

    PrintGrid(grid);
    printf("Puzzle generated with %d clues\n", clues);
    return;
}