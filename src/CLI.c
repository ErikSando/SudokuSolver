#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bool.h"
#include "CLI.h"
#include "Grid.h"
#include "Utility.h"

void GetFilePath(char* input, char* path) {
    char* ptr = input + 5;

    char savepath[MaxPathLength];
    int i = 0;

    while (ptr[i] != ' ' && ptr[i] != '\n' && ptr[i] != '\0') {
        savepath[i] = ptr[i];
        i++;

        if (i >= MaxPathLength) {
            printf("File path too long, maximum %d characters.\n", MaxPathLength);
            path[0] = InvalidPath;
        }
    }

    savepath[i] = '\0';
    memcpy(path, savepath, strlen(savepath) + 1);
}

void CommandLoop() {
    Grid grid[1];
    InitGrid(grid);

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
            // tgese aren't working correctly, so I've commented tgem out
            //printf("generate [difficulty]\n - Generate a grid layout with the chosen difficulty (0 to 5, lower meaning less difficult)\n");
            //printf("nsols\n - Check the number of solutions\n");
            //printf("solve\n - Solve the current grid layout\n");
            //printf("solve-rand\n - Solve the grid, but randomise the order of digits checked rather than using 1 -> 9\n");
            printf("save [save path]\n - Save the grid layout to the specified file path\n");
            printf("load [save path]\n - Load the grid layout from the specified file path\n");
            printf("profile\n - Test the speed of MakeMove and TakeMove, the functions used in the solving algorithm.\n");
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
                printf("Usage: place [digit] [row] [column]\n");
                continue;
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
                printf("Usage: clear [row] [column]\n");
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

            ClearCell(grid, (row - 1) * 9 + (col - 1));
            PrintGrid(grid);
		}
		else if (!strncmp(input, "print", 5)) {
            PrintGrid(grid);
		}
		else if (!strncmp(input, "generate", 8)) {
            int difficulty;

            if (sscanf(input + 9, "%d", &difficulty) != 1) {
                printf("Incorrect usage\n");
                printf("Usage: generate [difficulty]\n");
                continue;
            }

            if (difficulty < 0 || difficulty >= 6) {
                printf("Invalid difficulty, expected 0-5\n");
                continue;
            }

            GeneratePuzzle(grid, difficulty);
		}
		else if (!strncmp(input, "nsols", 5)) {
            int nsols = NumberOfSolutions(grid);

            if (!nsols) {
                printf("There are no solutions\n");
            }
            else if (nsols == 1) {
                printf("There is 1 solution\n");
            }
            else {
                printf("There are %d solutions\n", nsols);
            }
		}
		else if (!strncmp(input, "solve-rand", 10)) { // must come before solve
            Grid copy[1];
            InitGrid(copy);
            CopyGrid(grid, copy);

            int solvable = SolveGridRandomised(grid);

            if (!solvable) {
                printf("Grid has no solutions\n");
                CopyGrid(copy, grid);
                DestroyGrid(copy);
                continue;
            }

            PrintGrid(grid);
            DestroyGrid(copy);
		}
		else if (!strncmp(input, "solve", 5)) {
            Grid copy[1];
            InitGrid(copy);
            CopyGrid(grid, copy);

            int solvable = SolveGrid(grid);

            if (!solvable) {
                printf("Grid has no solutions\n");
                CopyGrid(copy, grid);
                DestroyGrid(copy);
                continue;
            }

            PrintGrid(grid);
            DestroyGrid(copy);

            // int nsols = NumberOfSolutions(grid);

            // if (!nsols) {
            //     printf("There are no solutions\n");
            // }
            // else {
            //     if (nsols > 1) {
            //         printf("There are multiple solutions, using first solution.\n");
            //     }

            //     SolveGrid(grid);
            // }
		}
		else if (!strncmp(input, "save", 4)) {
            char savepath[MaxPathLength];
            GetFilePath(input, savepath);

            if (savepath[0] == InvalidPath) continue;

            SaveGrid(grid, savepath);
		}
		else if (!strncmp(input, "load", 4)) {
            char savepath[MaxPathLength];
            GetFilePath(input, savepath);

            if (savepath[0] == InvalidPath) continue;

            LoadGrid(grid, savepath);
            PrintGrid(grid);
		}
		else if (!strncmp(input, "profile", 7)) {
            Grid _grid[1];
            InitGrid(_grid);

            int start = GetTimeMS();

            for (int i = 0; i < ProfileIterations; i++) {
                int cell = rand() % 81;
                int digit = rand() % 9 + 1;

                MakeMove(_grid, cell, digit);
                TakeMove(_grid);
            }

            int end = GetTimeMS();
            int duration = end - start;

            DestroyGrid(_grid);

            printf("Executed MakeMove followed by TakeMove %d times in %d ms\n", ProfileIterations, duration);
        }
        else {
            printf("Unknown command: %s", input);
        }
    }

    DestroyGrid(grid);
}