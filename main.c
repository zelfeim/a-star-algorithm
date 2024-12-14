#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    int x;
    int y;
} point;

int** map_file_to_grid(int* nrows, int* ncolumns);
void print_grid(int** grid, int nrows, int ncolumns);
point* find_shortest_path(int** grid, int nrows, int ncolumns);

int main() {
    // read file to tile array
    int nrows;
    int ncolumns;
    int** grid = map_file_to_grid(&nrows, &ncolumns);

    print_grid(grid, nrows, ncolumns);

    // algorithm returning shortest path

    free(grid);

    return 0;
}

int** map_file_to_grid(int* nrows, int* ncolumns) {
    *nrows = 20;
    *ncolumns = 20;

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
        printf("\nSave to col: %i and row: %i", col, row);
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
        printf("\nSaved value: %c", grid[col][row]);

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

float calculate(int x, int y) {

}

point* find_shortest_path(int** grid, int nrows, int ncolumns) {
    // TODO: don't use some magic value
    point* path = malloc(1024 * sizeof(point));

    point current_point = { 20, 0 };
    point finish_point = {0, 20};

    point* open_list[2048]; // TODO: dynamic
    point* closed_list[2048]; // TODO: dynamic

    point p;
    while(true) {
        // TODO: validate max and min point value
        // TODO: save to some object how many steps from the beggining we are
        // TODO: check blocker
        // calculate upper

        calculate(current_point.x - 1, current_point.y);

        // calculate lower

        // calculate left

        // calculate right
    }

    return path;
}
