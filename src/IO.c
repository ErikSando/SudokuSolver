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