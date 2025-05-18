#include <stdio.h>

#include "Grid.h"

#define SaveFileLength 163
#define SaveFileRowLength 18

void LoadGrid(Grid* grid, const char* savepath) {
    FILE* file = fopen(savepath, "r");

    if (file == NULL) {
        printf("Error opening file: %s\n", savepath);
        return;
    }

    char contents[SaveFileLength];

    int row = 0;

    while (row < 9 && fgets(contents, sizeof(contents), file)) {
        int col = 0;

        for (int i = 0; i < SaveFileRowLength; i++) {
            char c = contents[i];

            if (c >= '0' && c <= '9') {
                int cell = row * 9 + col;
                SetCell(grid, cell, c - '0');
                col++;
            }
        }

        row++;
    }

    fclose(file);
}