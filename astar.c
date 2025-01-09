#include "astar.h"
#include "point.h"
#include "cell.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

const point directions[4] = {{ 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 }};

float calculate_h(point current, point goal) {
    return sqrt(pow(current.x - goal.x, 2) + pow(current.y - goal.y, 2));
}

void reconstruct_path(cell current_cell, cell* path) {
    cell* path_cell = &current_cell;

    int path_index = 0;
    while(path_cell != NULL) {
        printf("(%d, %d)\n", path_cell->point.x, path_cell->point.y);
        path[path_index++] = *path_cell;
        path_cell = path_cell->parent;
    }
}

cell* new_path(int size) {
    cell* path = malloc(size * sizeof(cell));
    for(int i = 0; i < size; ++i) {
        path[i] = (cell){(point){-1, -1}, 0, 0, 0, NULL};
    }

    return path;
}

void remove_element(cell* array, int index, int* array_length) {
    for(int i = index; i < *array_length; ++i) {
        array[i] = array[i + 1];
    }
    --*array_length;
}

cell* a_star(int** grid, int nrows, int ncolumns) {
    const int arr_size = nrows * ncolumns;

    cell* path = new_path(arr_size);

    cell open_list[arr_size];
    cell closed_list[arr_size];
    int open_list_index = 0, closed_list_index = 0;

    const point start_point = { 0, 0 };
    const point finish_point = { nrows - 1, ncolumns - 1 };

    cell start_cell = { start_point, 0, calculate_h(start_point, finish_point), 0, NULL };
    start_cell.f = start_cell.g + start_cell.h;
    open_list[open_list_index++] = start_cell;

    while(1) {
        // Find last element with lowest f value
        int current_index = 0;
        for(int i = 0; i < open_list_index; ++i) {
            float diff = open_list[i].f - open_list[current_index].f;

            if(diff <= 0) {
                current_index = i;
            }
        }

        cell current_cell = open_list[current_index];
        remove_element(open_list, current_index, &open_list_index);
        printf("CURRENT CELL: (%d, %d) - g: %d, h: %f, f: %f\n", current_cell.point.x, current_cell.point.y, current_cell.g, current_cell.h, current_cell.f);

        if(current_cell.point.x == finish_point.x && current_cell.point.y == finish_point.y) {
            printf("FOUND PATH, END ALGORITHM.\n\n");
            reconstruct_path(current_cell, path);

            return path;
        }

        closed_list[closed_list_index++] = current_cell;

        // Check all directions
        for(int i = 0; i < 4; ++i) {
            point new_point = { current_cell.point.x + directions[i].x, current_cell.point.y + directions[i].y };

            printf("\tCHECKED POINT: (%d, %d)\n", new_point.x, new_point.y);

            if(new_point.x < 0 || new_point.x > nrows - 1 || new_point.y < 0 || new_point.y > ncolumns - 1) {
                printf("\t\tOut of bounds, skip!\n");

                continue;
            }

            if((char)grid[new_point.x][new_point.y] == '5') {
                printf("\t\tObstacle! Skip\n");

                continue;
            }

            int in_closed_list = 0;
            for(int j = 0; j < closed_list_index; ++j) {
                if(closed_list[j].point.x == new_point.x && closed_list[j].point.y == new_point.y) {
                    in_closed_list = 1;

                    break;
                }
            }
            if(in_closed_list) {
                printf("\t\tIn closed list! Skip\n");

                continue;
            }

            int g = current_cell.g + 1;
            float h = calculate_h(new_point, finish_point);
            float f = g + h;

            int in_open = 0;
            for(int j = 0; j < open_list_index; ++j) {
                if(open_list[j].point.x == new_point.x && open_list[j].point.y == new_point.y) {
                    printf("\t\tCell already exists in open list!\n");
                    in_open = 1;

                    break;
                }
            }
            if(!in_open) {
                cell new_cell = { new_point, g, h, f, &closed_list[closed_list_index - 1] };
                open_list[open_list_index++] = new_cell;
            }
        }
    }

    return path;
}
