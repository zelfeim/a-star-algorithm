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

    int row = 0;
    int col = 4;
    do {
        c = (char)fgetc(f);

        if(c == ' ') {
            continue;
        }

        if(c == '\n') {
            col--;
            row = 0;

            continue;
        }

        grid[row][col] = (int)c;
        row++;
    } while(c != EOF);

    fclose(f);

    return grid;
}

void print_grid(int** grid, int nrows, int ncolumns) {
    for(int y = nrows - 1; y >= 0; --y) {
        for(int x = 0; x < ncolumns; ++x) {
            printf("%c ", grid[x][y]);
        }
        printf("\n");
    }
}

void path_to_grid(cell* path, int** grid) {
    for(int i = 0; path[i].point.x != -1 && path[i].point.y != -1; ++i) {
        grid[path[i].point.x][path[i].point.y] = '3';
    }
}

void draw_grid() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    for(int i = 0; i <= 5; ++i) {
        glVertex2f(i * 1, 0);
        glVertex2f(i * 1, 5);

        glVertex2f(0, i * 1);
        glVertex2f(5, i * 1);
    }
    glEnd();
}

void draw_cell(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);

    glBegin(GL_QUADS);
    glVertex2f(x * 1, y * 1);
    glVertex2f((x + 1) * 1, y * 1);
    glVertex2f((x + 1) * 1, (y + 1) * 1);
    glVertex2f(x * 1, (y + 1) * 1);
    glEnd();
}

void draw_cells(int** grid, int nrows, int ncolumns) {
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncolumns; ++j) {
            switch (grid[i][j]) {
                case '0':
                    draw_cell(i, j, 0.2f, 0.2f, 0.2f);
                    break;
                case '3':
                    draw_cell(i, j, 0.0f, 0.6f, 0.0f);
                    break;
                case '5':
                    draw_cell(i, j, 0.6f, 0.0f, 0.0f);
                    break;
            }
        }
    }
}

int main() {
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

    if(!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "AStar Algorithm", NULL, NULL);
    if(!window) {

        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glOrtho(0, 5, 0, 5, -1.0, 1.0);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw_cells(grid, nrows, ncolumns);
        draw_grid();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
