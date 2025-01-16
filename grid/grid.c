#include <stdio.h>
#include <stdlib.h>

#include "grid.h"

int** map_file_to_grid(int* nrows, int* ncolumns) {
    *nrows = 20;
    *ncolumns = 20;

    int** grid = malloc(*nrows * sizeof(int*));
    for(int i = 0; i < *nrows; ++i) {
        grid[i] = malloc(*ncolumns * sizeof(int));
    }

    FILE* f = fopen("grid.txt", "r");

    if(f == NULL) {
        printf("Can't open the file");
        return 0;
    }

    int row = 0;
    int col = 19;

    char c;
    while((c = fgetc(f)) != EOF) {
        if(c == ' ') {
            continue;
        }

        if(c == '\r') {
            continue;
        }

        if(c == '\n') {
            col--;
            row = 0;

            continue;
        }

        grid[row][col] = (int)c;
        row++;
    }

    fclose(f);

    return grid;
}

void print_grid(int** grid, int nrows, int ncolumns) {
    for(int y = nrows - 1; y >= 0; --y) {
        for(int x = 0; x < ncolumns; ++x) {
            printf("%c ", grid[x][y]);
        }
        printf("\n");
    }
}

void path_to_grid(cell* path, int** grid) {
    for(int i = 0; path[i].point.x != -1 && path[i].point.y != -1; ++i) {
        int x = path[i].point.x;
        int y = path[i].point.y;

        if(grid[x][y] == '1' || grid[x][y] == '2') {
            continue;
        }

        grid[x][y] = '3';
    }
}

void clear_path_from_grid(int** grid, int nrows, int ncolumns) {
    for(int y = 0; y < ncolumns; ++y) {
        for(int x = 0; x < nrows; ++x) {
            if(grid[y][x] == '3') {
                grid[y][x] = '0';
            }
        }
    }
}
