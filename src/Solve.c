#include "Bool.h"
#include "Grid.h"
#include "Utility.h"

int NumberOfSolutions(Grid* grid) {
    int cell = InvalidCell;

    for (int i = 0; i < 81; i++) {
        if (!grid->cells[i]) {
            cell = i;
            break;
        }
    }

    if (cell == InvalidCell) return 1;

    int solutions = 0;

    for (int digit = 1; digit <= 9; digit++) {
        if (!GetBit(grid->candidates[cell], digit - 1)) continue;

        MakeMove(grid, cell, digit);
        solutions += NumberOfSolutions(grid);
        TakeMove(grid);
    }

    return solutions;
}

int SolveGrid(Grid* grid) {
    int cell = InvalidCell;

    for (int i = 0; i < 81; i++) {
        if (!grid->cells[i]) {
            cell = i;
            break;
        }
    }

    if (cell == InvalidCell) return True;

    for (int digit = 1; digit <= 9; digit++) {
        if (!GetBit(grid->candidates[cell], digit - 1)) continue;
        MakeMove(grid, cell, digit);
        if (SolveGrid(grid)) return True;
        TakeMove(grid);
    }

    return False;
}

int SolveGridRandomised(Grid* grid) {
    int cell = InvalidCell;

    for (int i = 0; i < 81; i++) {
        if (!grid->cells[i]) {
            cell = i;
            break;
        }
    }

    if (cell == InvalidCell) return True;
    
    int digits[9];
    GetRandomOrder(digits);

    for (int i = 0; i < 9; i++) {
        if (!GetBit(grid->candidates[cell], digits[i] - 1)) continue;
        MakeMove(grid, cell, digits[i]);
        if (SolveGridRandomised(grid)) return True;
        TakeMove(grid);
    }

    return False;
}