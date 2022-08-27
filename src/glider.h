#define WIDTH 80
#define HEIGHT 25

void glider(char matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 3 && (j > 0 && j < 4)) {
                matrix[i][j] = '0';
            }
            else if (i == 2 && j == 3) {
                matrix[i][j] = '0';
            }
            else if (i == 1 && j == 2) {
                matrix[i][j] = '0';
            }
            else {
                matrix[i][j] = '.';
            }
        }
    }
}
