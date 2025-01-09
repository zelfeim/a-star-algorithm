#include "./grid/grid.h"
#include "./cell/cell.h"
#include "./astar/astar.h"

int main() {
    int nrows;
    int ncolumns;
    int** grid = map_file_to_grid(&nrows, &ncolumns);

    if(grid == 0) {
        return 1;
    }

    print_grid(grid, nrows, ncolumns);

    cell* path = a_star(grid, nrows, ncolumns);
    path_to_grid(path, grid);

    print_grid(grid, nrows, ncolumns);

    return 0;
}
