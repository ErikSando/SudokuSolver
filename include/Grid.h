#ifndef GRID_H
#define GRID_H

typedef unsigned char U8;
typedef unsigned short int U16;

#define IsCandidate(candidates, digit) ((candidates) & (1ULL << ((digit) - 1)))
#define AddCandidate(candidates, digit) ((candidates) |= (1ULL << ((digit) - 1)))
#define RemoveCandidate(candidates, digit) ((candidates) &= ~(1ULL << ((digit) - 1)))

typedef struct {
    U8 cells[81];
    U16 candidates[81];

} Grid;

extern void ResetGrid(Grid* grid);

extern void SetCell(Grid* grid, int cell, int digit);
extern void ClearCell(Grid* grid, int cell);

extern int SaveGrid(Grid* grid, const char* savepath);
extern void LoadGrid(Grid* grid, const char* savepath);

extern void PrintGrid(Grid* grid);

#endif