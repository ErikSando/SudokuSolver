#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Assert.h"
#include "Grid.h"

void ClearGridHistory(Grid* grid) {
    for (int i = 0; i < 81; i++) {
        memset(grid->history[i].cells, 0, sizeof(grid->history[i].cells));

        for (int cell = 0; cell < 81; cell++) {
            grid->history[i].candidates[cell] = 0b111111111;
        }
    }
}

void InitGridHistory(Grid* grid) {
    //grid->history = NULL;
    //free(grid->history);
    grid->history = (GridState*) malloc(81 * sizeof(GridState));

    if (!grid->history) {
        fprintf(stderr, "Failed to allocate memory for grid history\n");
        exit(1);
    }

    ClearGridHistory(grid);
}

void ResetGrid(Grid* grid) {
    memset(grid->cells, 0, sizeof(grid->cells));

    for (int cell = 0; cell < 81; cell++) {
        grid->candidates[cell] = 0b111111111;
    }

    grid->move = 0;
}

void InitGrid(Grid* grid) {
    ResetGrid(grid);
    InitGridHistory(grid);
}

void DestroyGrid(Grid* grid) {
    free(grid->history);
}

void SetCell(Grid* grid, int cell, int digit) {
    grid->cells[cell] = digit;
    grid->candidates[cell] = 0;

    int col_start = cell % 9;
    int row_start = cell - col_start;

    for (int i = 0; i < 9; i++) {
        int cell1 = col_start + i * 9;
        int cell2 = row_start + i;

        Assert(cell1 >= 0 && cell1 < 81);
        Assert(cell2 >= 0 && cell2 < 81);

        ClearBit(grid->candidates[cell1], digit - 1);
        ClearBit(grid->candidates[cell2], digit - 1);
    }

    int row = row_start / 9;

    int subgrid_row = row % 3;
    int subgrid_col = col_start % 3;
    int subgrid_topleft = (row - subgrid_row) * 9 + col_start - subgrid_col;

    for (int c = 0; c < 3; c++) {
        for (int r = 0; r < 3; r++) {
            int index = subgrid_topleft + r * 9 + c;
            ClearBit(grid->candidates[index], digit - 1);
        }
    }
}

void ClearCell(Grid* grid, int cell) {
    U8 digit = grid->cells[cell];
    grid->cells[cell] = 0;

    if (digit < 1) return;

    int col_start = cell % 9;
    int row_start = cell - col_start;

    for (int i = 0; i < 9; i++) {
        int cell1 = col_start + i * 9;
        int cell2 = row_start + i;

        Assert(cell1 >= 0 && cell1 < 81);
        Assert(cell2 >= 0 && cell2 < 81);

        SetBit(grid->candidates[cell1], digit - 1);
        SetBit(grid->candidates[cell2], digit - 1);
    }

    int row = row_start / 9;

    int subgrid_row = (row / 9) % 3;
    int subgrid_col = col_start % 3;
    int subgrid_topleft = (row - subgrid_row) * 9 + col_start - subgrid_col;

    for (int c = 0; c < 3; c++) {
        for (int r = 0; r < 3; r++) {
            int index = subgrid_topleft + r * 9 + c;
            Assert(index >= 0 && index < 81);
            SetBit(grid->candidates[index], digit - 1);
        }
    }
}

void MakeMove(Grid* grid, int cell, int digit) {
    if (grid->move >= 81) {
        fprintf(stderr, "Grid history overflow\n");
        exit(1);
    }

    GridState* gs = &grid->history[grid->move++];

    Assert(grid->move > 0);

    memcpy(gs->cells, grid->cells, sizeof(gs->cells));
    memcpy(gs->candidates, grid->candidates, sizeof(gs->candidates));

    SetCell(grid, cell, digit);
}

void TakeMove(Grid* grid) {
    if (grid->move < 1) {
        printf("No previous moves to revert to\n");
        return;
    }

    GridState previous = grid->history[--grid->move];

    memcpy(grid->cells, previous.cells, sizeof(grid->cells));
    memcpy(grid->candidates, previous.candidates, sizeof(grid->candidates));
}