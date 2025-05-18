#ifndef GRID_H
#define GRID_H

typedef unsigned char U8;
typedef unsigned short int U16;

#define GetBit(bits, bit) ((bits) & (1U << (bit)))
#define SetBit(bits, bit) ((bits) |= (1U << (bit)))
#define ClearBit(bits, bit) ((bits) &= ~(1U << (bit)))

typedef struct {
    U8 cells[81];
    U16 candidates[81];

} GridState;

typedef struct {
    U8 cells[81];
    U16 candidates[81];

    int move;

    GridState* history;
    int max_moves;

} Grid;

extern void ResetGrid(Grid* grid);
extern void InitGrid(Grid* grid);
extern void DestroyGrid(Grid* grid);

extern void SetCell(Grid* grid, int cell, int digit);
extern void ClearCell(Grid* grid, int cell);
extern void MakeMove(Grid* grid, int cell, int digit);
extern void TakeMove(Grid* grid);

extern void SaveGrid(Grid* grid, const char* savepath);
extern void LoadGrid(Grid* grid, const char* savepath);

extern int NumberOfSolutions(Grid* grid);
extern void SolveGrid(Grid* grid);

extern void PrintGrid(Grid* grid);

#endif