#include <stdio.h>

#include "Grid.h"

void LoadGrid(Grid* grid, const char* savepath) {
    FILE* file = fopen(savepath, "r");

    if (file == NULL) {
        printf("Error opening file: %s\n", savepath);
        return;
    }

    char contents_buffer[163];
}