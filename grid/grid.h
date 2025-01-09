#ifndef GRID_H_
#define GRID_H_

#include "../cell/cell.h"

int** map_file_to_grid(int* nrows, int* ncolumns);

void print_grid(int** grid, int nrows, int ncolumns);

void path_to_grid(cell* path, int** grid);

#endif // GRID_H_
