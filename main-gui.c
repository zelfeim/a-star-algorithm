#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./cell/cell.h"
#include "./grid/grid.h"
#include "./astar/astar.h"

void draw_grid() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    for(int i = 0; i <= 20; ++i) {
        glVertex2f(i * 1, 0);
        glVertex2f(i * 1, 20);

        glVertex2f(0, i * 1);
        glVertex2f(20, i * 1);
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
                    draw_cell(i, j, 0.0f, 0.0f, 0.0f);
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

    cell* path = a_star(grid, nrows, ncolumns);
    path_to_grid(path, grid);

    if(!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "AStar Algorithm", NULL, NULL);
    if(!window) {

        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glOrtho(0, ncolumns, 0, ncolumns, -1.0, 1.0);

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
