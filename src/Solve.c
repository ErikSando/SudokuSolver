#include "Grid.h"

int NumberOfSolutions(Grid* grid) {
    int solutions = 0;
    int free_cells = 0;

    for (int cell = 0; cell < 81; cell++) {
        //int n_candidates = NumberOfBits(grid->candidates[i]);
        int candidates = 0;

        for (int digit = 1; digit <= 9; digit++) {
            if (!GetBit(grid->candidates[cell], digit - 1)) continue;

            MakeMove(grid, cell, digit);
            solutions += NumberOfSolutions(grid);
            TakeMove(grid);

            candidates++;
        }

        if (candidates > 0) free_cells++;
    }

    if (!free_cells) return 1;

    return solutions;
}