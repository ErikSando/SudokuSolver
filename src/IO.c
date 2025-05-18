#include <stdio.h>

#include "Grid.h"

void PrintGrid(Grid* grid) {
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0) printf(" -------------------------\n");

        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0) printf(" |");

            int cell = row * 9 + col;
            char c = '.';

            if (grid->cells[cell]) {
                c = '0' + grid->cells[cell];
            }

            printf(" %c", c);
        }

        printf(" |\n");
    }

    printf(" -------------------------\n");
}

void PrintCandidates(U16 candidates) {
    for (int digit = 1; digit <= 9; digit++) {
        printf(" %d", digit);
    }

    printf("\n");

    for (int bit = 0; bit < 9; bit++) {
        printf(" %d", GetBit(candidates, bit));
    }

    printf("\n");
}