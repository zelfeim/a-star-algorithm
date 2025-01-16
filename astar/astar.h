#ifndef ASTAR_H_
#define ASTAR_H_

typedef struct point point;
typedef struct cell cell;

cell* a_star(int** grid, int nrows, int ncolumns, point start_point, point finish_point);

#endif // ASTAR_H_
