#ifndef CELL_H_
#define CELL_H_

#include "point.h"

typedef struct cell {
    point point;
    int value;

    int g;
    float f;

    struct cell* parent;
} cell;

#endif // CELL_H_
