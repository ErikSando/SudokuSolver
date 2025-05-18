#include <stdio.h>

#include "Bool.h"
#include "Grid.h"

int SaveGrid(Grid* grid, const char* savepath) {
    FILE* file = fopen(savepath, "w");

    if (file == NULL) {
        printf("Error opening file: %s\n", savepath);
        return False;
    }

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int cell = row * 9 + col;
            fprintf(file, "%i ", grid->cells[cell]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    return True;
}