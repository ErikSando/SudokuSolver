#include <stdio.h>
#include <string.h>

#include "Bool.h"
#include "CLI.h"
#include "Grid.h"

void CommandLoop() {
    Grid grid[1];

    ResetGrid(grid);

    setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	char input[InputBufferSize];

    for (;;) {
        memset(input, 0, sizeof(input));

		fflush(stdout);

		if (!fgets(input, InputBufferSize, stdin) || input[0] == '\n') continue;

        if (!strncmp(input, "help", 4)) {
			printf("help\n - Prints this menu\n");
			printf("exit\n - Exit the program.\n");
            printf("reset\n - Reset the grid\n");
            printf("place [digit] [row] [column]\n - Place a digit on the grid in the specified row and column\n");
            printf("clear [row] [column]\n - Reset the cell at the specified row and column\n");
            printf("print\n - Print the grid\n");
            printf("generate [difficulty]\n - Generate a grid layout with the chosen difficulty (0 to 3, lower meaning less difficult)\n");
            printf("nsols\n - Check the number of solutions\n");
            printf("solve\n - Solve the current grid layout\n");
            printf("save [save path]\n - Save the grid layout to the specified file path\n");
            printf("load [save path]\n - Load the grid layout from the specified file path\n");
		}
        else if (!strncmp(input, "exit", 4)) {
            break;
        }
		else if (!strncmp(input, "reset", 5)) {
            ResetGrid(grid);
            PrintGrid(grid);
		}
		else if (!strncmp(input, "place", 5)) {
            int digit, row, col;

            if (sscanf(input + 6, "%d %d %d", &digit, &row, &col) != 3) {
                printf("Incorrect usage\n");
                printf("Usage: place [digit] [row] [column]");
            }

            if (digit < 1 || digit > 9) {
                printf("Invalid digit, expected 1-9\n");
                continue;
            }

            if (row < 1 || row > 9) {
                printf("Invalid row, expected 1-9\n");
                continue;
            }

            if (col < 1 || col > 9) {
                printf("Invalid column, expected 1-9\n");
                continue;
            }

            SetCell(grid, (row - 1) * 9 + (col - 1), digit);
            PrintGrid(grid);
		}
		else if (!strncmp(input, "clear", 5)) {
            int row, col;

            if (sscanf(input + 6, "%d %d", &row, &col) != 2) {
                printf("Incorrect usage\n");
                printf("Usage: clear [row] [column]");
            }

            if (row < 1 || row > 9) {
                printf("Invalid row, expected 1-9\n");
                continue;
            }

            if (col < 1 || col > 9) {
                printf("Invalid column, expected 1-9\n");
                continue;
            }

            ClearCell(grid, (row - 1) * 9 + (col - 1));
            PrintGrid(grid);
		}
		else if (!strncmp(input, "print", 5)) {
            PrintGrid(grid);
		}
		else if (!strncmp(input, "generate", 8)) {
		}
		else if (!strncmp(input, "nsols", 5)) {
		}
		else if (!strncmp(input, "solve", 5)) {
		}
		else if (!strncmp(input, "save", 4)) {
            char* ptr = input + 5;
            
            char savepath[InputBufferSize - 6];
            int i = 0;

            int fail = False;

            while (ptr[i] != ' ' && ptr[i] != '\n' && ptr[i] != '\0') {
                savepath[i] = ptr[i];
                i++;

                if (i >= InputBufferSize - 6) {
                    printf("File path too long, maximum %d characters.\n", InputBufferSize - 6);
                    fail = True;
                    break;
                }
            }

            if (fail) continue;

            savepath[i] = '\0';

            if (SaveGrid(grid, savepath)) {
                printf("Saved grid to %s\n", savepath);
            }
		}
		else if (!strncmp(input, "load", 4)) {
		}
    }
}