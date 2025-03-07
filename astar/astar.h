#ifndef ASTAR_H_
#define ASTAR_H_

typedef struct point point;
typedef struct cell cell;

float calculate_h(point current, point goal);
cell* a_star(int** grid, int nrows, int ncolumns, point start_point, point finish_point, int* path_length);

#endif // ASTAR_H_
