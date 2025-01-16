#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./cell/cell.h"
#include "./grid/grid.h"
#include "./astar/astar.h"

#include <stdbool.h>
#include <stdio.h>

enum State {
    SETUP,
    DRAW_PATH,
    RUN_ALGORITHM
};

struct Application {
    enum State state;
    int** grid;
    point start_point;
    point finish_point;
    int algorithm_run;

    bool user_drawn_path;
};

void draw_grid() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    for(int i = 0; i <= 20; ++i) {
         glVertex2f(i * 1, 0);
         glVertex2f(i * 1, 40);

         glVertex2f(0, i * 1);
         glVertex2f(40, i * 1);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    struct Application* application = glfwGetWindowUserPointer(window);

    // Close the window
    if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
        application->state = -1;
    }

    // Run algorithm and draw its results
    if(key == GLFW_KEY_S && action == GLFW_PRESS && application->start_point.x != -1 && application->start_point.x != -1 && application->finish_point.x != -1 && application->finish_point.y != -1) {
        application->state = RUN_ALGORITHM;
        application->algorithm_run = 0;
    }

    if(key == GLFW_KEY_D && action == GLFW_PRESS && application->state == SETUP) {
        application->user_drawn_path = 1;
        application->state = DRAW_PATH;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    struct Application* application = glfwGetWindowUserPointer(window);

    double cell_width = 800.0f/20;
    double cell_height = 600.0f/20;

    double x_pos, y_pos;
    glfwGetCursorPos(window, &x_pos, &y_pos);

    int x = x_pos / cell_width;
    int y = 20 - (y_pos / cell_height);

    // Select the cells
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int* val = &application->grid[x][y];
        if(application->state == RUN_ALGORITHM) {
            clear_path_from_grid(application->grid, 20, 20);
            application->state = SETUP;
        }

        if(application->state == SETUP) {
            if(*val == '5') {
                *val = '0';
            } else {
                *val = '5';
            }
        } else if(application->state == DRAW_PATH) {
            if(*val == '0') {
                *val = '9';
            }
        }
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && application->state == SETUP) {
        if(application->start_point.x == -1 && application->start_point.y == -1) {
            application->start_point.x = x;
            application->start_point.y = y;
            application->grid[x][y] = '1';
        } else if(application->finish_point.x == -1 && application->finish_point.y == -1) {
            application->finish_point.x = x;
            application->finish_point.y = y;
            application->grid[x][y] = '2';
        }
    }
}

void draw_cells(int** grid, int nrows, int ncolumns) {
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncolumns; ++j) {
            switch (grid[i][j]) {
                case '0':
                    draw_cell(i, j, 0.0f, 0.0f, 0.0f);
                    break;
                case '1':
                    draw_cell(i, j, 0.0f, 1.0f, 0.0f);
                    break;
                case '2':
                    draw_cell(i, j, 1.0f, 0.0f, 0.0f);
                    break;
                case '3':
                    draw_cell(i, j, 0.6f, 0.6f, 0.0f);
                    break;
                case '5':
                    draw_cell(i, j, 0.5f, 0.5f, 0.5f);
                    break;
                case '7':
                    draw_cell(i, j, 0.6f, 0.6f, 1.0f);
                    break;
                case '9':
                    draw_cell(i, j, 0.0f, 0.8f, 1.0f);
                    break;
            }
        }
    }
}

int main() {
    int nrows, ncolumns;
    struct Application application = {
        .state = SETUP,
        .grid = map_file_to_grid(&nrows, &ncolumns),
        .start_point = {.x = -1, .y = -1},
        .finish_point = {.x = -1, .y = -1},
        .algorithm_run = 0,
        .user_drawn_path = 0
    };

    if(application.grid == NULL) {
        return 1;
    }

    if(!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "AStar Algorithm", NULL, NULL);
    if(!window) {

        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    glOrtho(0, nrows, 0, ncolumns, -1.0, 1.0);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetWindowUserPointer(window, &application);

    cell* path;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(application.state == RUN_ALGORITHM) {
            if(application.algorithm_run == 0) {
                path = a_star(application.grid, nrows, ncolumns, application.start_point, application.finish_point);
                path_to_grid(path, application.grid);
                application.algorithm_run = 1;
            }
        }

        draw_cells(application.grid, nrows, ncolumns);
        draw_grid();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
