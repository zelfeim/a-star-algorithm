#ifndef CELL_H_
#define CELL_H_

#include "../point/point.h"

typedef struct cell {
    point point;

    int g;   // distance from start
    float h; // heuristics
    float f; // sum of values

    struct cell* parent;
} cell;

#endif // CELL_H_
