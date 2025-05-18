#ifndef GRID_H
#define GRID_H

typedef unsigned char U8;
typedef unsigned short int U16;

#define GetBit(bits, bit) (((bits) >> bit) & 1U)
#define SetBit(bits, bit) ((bits) |= (1U << (bit)))
#define ClearBit(bits, bit) ((bits) &= ~(1U << (bit)))

#define InvalidCell -1

extern const int NumberOfClues[6];

typedef struct {
    U8 cells[81];
    U16 candidates[81];

} GridState;

typedef struct {
    U8 cells[81];
    U16 candidates[81];

    int move;

    GridState* history;

} Grid;

extern void ResetGrid(Grid* grid);
extern void InitGrid(Grid* grid);
extern void DestroyGrid(Grid* grid);

extern void SetCell(Grid* grid, int cell, int digit);
extern void MakeMove(Grid* grid, int cell, int digit);
extern void TakeMove(Grid* grid);
extern void ClearCell(Grid* grid, int cell);

extern void CopyGrid(Grid* grid, Grid* copy);

extern void SaveGrid(Grid* grid, const char* savepath);
extern void LoadGrid(Grid* grid, const char* savepath);

extern int NumberOfSolutions(Grid* grid);
extern int SolveGrid(Grid* grid);
extern int SolveGridRandomised(Grid* grid);

extern void GeneratePuzzle(Grid* grid, const int difficulty);

extern void PrintGrid(Grid* grid);
extern void PrintCandidates(U16 candidates);

#endif