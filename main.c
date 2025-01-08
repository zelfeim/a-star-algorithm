#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "astar.h"

#include "cell.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int** map_file_to_grid(int* nrows, int* ncolumns) {
    *nrows = 5;
    *ncolumns = 5;

    int** grid = malloc(*nrows * sizeof(int*));
    for(int i = 0; i < *nrows; ++i) {
        grid[i] = malloc(*ncolumns * sizeof(int));
    }

    FILE* f = fopen("grid.txt", "r");
    char c;

    if(f == NULL) {
        printf("Can't open the file");
        return NULL;
    }

    int col = 0;
    int row = 0;
    do {
        c = (char)fgetc(f);

        if(c == ' ') {
            continue;
        }

        if(c == '\n') {
            row++;
            col = 0;

            continue;
        }

        grid[col][row] = (int)c;
        col++;
    } while(c != EOF);

    return grid;
}

void print_grid(int** grid, int nrows, int ncolumns) {
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncolumns; ++j) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void path_to_grid(cell* path, int** grid) {
    for(int i = 0; path[i].point.x != -1 && path[i].point.y != -1; ++i) {
        grid[path[i].point.x][path[i].point.y] = '3';
    }
}

int main() {
    // read file to tile array
    int nrows;
    int ncolumns;
    int** grid = map_file_to_grid(&nrows, &ncolumns);

    if(grid == NULL) {
        return 1;
    }

    print_grid(grid, nrows, ncolumns);

    cell* path = a_star(grid, nrows, ncolumns);
    path_to_grid(path, grid);

    print_grid(grid, nrows, ncolumns);

    free(path);
    free(grid);

    return 0;
}
