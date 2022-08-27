#include <stdio.h>

#include "glider.h"

#define WIDTH 80
#define HEIGHT 25

void output(char matrix[HEIGHT][WIDTH]);

int main() {
    char matrix[HEIGHT][WIDTH];
    glider(matrix);
    output(matrix);
}

void output(char matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

                     
                     
                     
                     
