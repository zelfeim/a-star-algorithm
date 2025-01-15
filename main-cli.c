#include "./grid/grid.h"
#include "./cell/cell.h"
#include "./astar/astar.h"

#include <stdio.h>

int main() {
    int nrows;
    int ncolumns;
    int** grid = map_file_to_grid(&nrows, &ncolumns);

    if(grid == 0) {
        return 1;
    }

    print_grid(grid, nrows, ncolumns);

    cell* path = a_star(grid, nrows, ncolumns);
    if(path[0].point.x == -1 && path[0].point.y == -1) {
        printf("No path was found!\n");
        return 1;
    }

    path_to_grid(path, grid);

    print_grid(grid, nrows, ncolumns);

    return 0;
}
