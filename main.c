#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tile {
    int x;
    int y;
    bool is_blocker;
};

int** map_file_to_tiles();

int main() {
    // read file to tile array
    map_file_to_tiles();

    // algorithm returning shortest path

    return 0;
}

int* map_file_to_tiles() {
    int tiles[20][20];

    FILE* f = fopen("grid.txt", "r");
    char c;

    if(f == NULL) {
        printf("Can't open the file");
        return NULL;
    }

    int col = 0;
    int row = 0;
    do {
        printf("\nSave to col: %i and row: %i", col, row);
        c = (char)fgetc(f);

        if(c == ' ') {
            continue;
        }

        if(c == '\n') {
            row++;
            col = 0;

            continue;
        }

        tiles[col][row] = (int)c;
        printf("\nSaved value: %c", tiles[col][row]);

        col++;
    } while(c != EOF);

    // return tiles;
}
