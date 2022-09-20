#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 25

void read_file(char matrix[HEIGHT][WIDTH], int m, int n, char name[]);
void clearall();
void output(char matrix[HEIGHT][WIDTH]);
void output_1(int matrix[HEIGHT][WIDTH]);
void check_1(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_2_horizontal(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_2_vertical(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_corner_left_high(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_corner_right_high(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_corner_left_bottom(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_corner_right_bottom(char matrix[HEIGHT][WIDTH], int i, int j, int *count);
void check_all(char matrix[HEIGHT][WIDTH], int m, int n, char data[HEIGHT][WIDTH]);
void zapis(char matrix[HEIGHT][WIDTH], char data[HEIGHT][WIDTH]);
void reading(char matrix[HEIGHT][WIDTH], int m, int n);
void choise(char matrix[HEIGHT][WIDTH], int m, int n, char name_1[], char name_2[],
            char name_3[], char name_4[], char name_5[]);

int main() {
    char matrix[HEIGHT][WIDTH];
    char data[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            data[i][j] = ' ';
        }
    }
    int m = 25, n = 80;
    char name_1[] = "glider.txt";
    char name_2[] = "turtle.txt";
    char name_3[] = "hiv.txt";
    char name_4[] = "randd.txt";
    char name_5[] = "gun.txt";
    choise(matrix, m, n, name_1, name_2, name_3, name_4, name_5);
    output(matrix);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = matrix[i][j];
        }
    }
    printf("\n");
    while (1) {
        clearall();
        check_all(matrix, m, n, data);
        output(data);
        zapis(matrix, data);
        printf("Нажмите ctrl + c, чтобы выйти\n");
        usleep(50000);
    }
}

void choise(char matrix[HEIGHT][WIDTH], int m, int n, char name_1[], char name_2[],
            char name_3[], char name_4[], char name_5[]) {
    printf("Введите варианты начального паттерна:\n");
    printf("1. glider \n");
    printf("2. turtle \n");
    printf("3. hiv \n");
    printf("4. rand \n");
    printf("5. gun \n");
    int s;
    scanf("%d", &s);
    if (s == 1) {
        read_file(matrix, m, n, name_1);
    }
    if (s == 2) {
        read_file(matrix, m, n, name_2);
    }
    if (s == 3) {
        read_file(matrix, m, n, name_3);
    }
    if (s == 4) {
        read_file(matrix, m, n, name_4);
    }
    if (s == 5) {
        read_file(matrix, m, n, name_5);
    }
}

void clearall() {
    printf("\e[1;1H\e[2J");
}

void read_file(char matrix[HEIGHT][WIDTH], int m, int n, char name[]) {
    FILE * doc = fopen(name, "r");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(doc, "%c", &matrix[i][j]);
//            printf("%c", matrix[i][j]);
            if (matrix[i][j] == '0') {
                matrix[i][j] = ' ';
            } else {
                matrix[i][j] = 'o';
            }
        }
    }
    fclose(doc);
}

void zapis(char matrix[HEIGHT][WIDTH], char data[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = data[i][j];
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            data[i][j] = ' ';
        }
    }
}

void output(char matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void check_all(char matrix[HEIGHT][WIDTH], int m, int n, char data[HEIGHT][WIDTH]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int count = 0;
            if (i > 0 && i < m - 1 && j > 0 && j < n - 1) {
                                                 // обработка центральной матрицы
                check_1(matrix, i, j, &count);
            }
            if (i > 0 && i < m - 1 && (j == 0 || j == n - 1)) {
                                      // обработка первого и последнего столбца без угловых элементов
                check_2_vertical(matrix, i, j, &count);
            }
            if ((i == 0 || i == m - 1) && (j > 0 && j < n - 1)) {
                                      // обработка первой и последней строчки без угловых элементов
                check_2_horizontal(matrix, i, j, &count);
            }
            if (i == 0 && j == 0) {
                check_corner_left_high(matrix, i, j, &count);
            }
            if (i == m - 1 && j == 0) {
                check_corner_left_bottom(matrix, i, j, &count);
            }
            if (i == 0 && j == n - 1) {
                check_corner_right_high(matrix, i, j, &count);
            }
            if (i == m - 1 && j == n - 1) {
                check_corner_right_bottom(matrix, i, j, &count);
            }
            if (matrix[i][j] == 'o' && (count < 2 || count > 3)) {
                data[i][j] = ' ';
            }
            if (matrix[i][j] == ' ' && count == 3) {
                data[i][j] = 'o';
            }
            if (matrix[i][j] == 'o' && (count == 2 || count == 3)) {
                data[i][j] = 'o';
            }
        }
    }
}

void check_1(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    *count = 0;
    for (int k = i - 1; k < i + 2; k++) {
        for (int l = j - 1; l < j + 2; l++) {
            if (k == i && l == j) {
                continue;
            }
            if (matrix[k][l] == 'o') {
                *count += 1;
            }
        }
    }
}

void check_2_horizontal(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    *count = 0;
    if (HEIGHT - 1 - i >= i) {
        for (int k = i; k < i + 2; k++) {
            for (int l = j - 1; l < j + 2; l++) {
                if (k == i && l == j) {
                    continue;
                }
                if (matrix[k][l] == 'o') {
                    *count += 1;
                }
            }
        }
        for (int o = j - 1; o < j + 2; o++) {
            if (matrix[HEIGHT - 1][o] == 'o') {
                *count += 1;
            }
        }
    } else {
        for (int k = i - 1; k < i + 1; k++) {
            for (int l = j - 1; l < j + 2; l++) {
                if (k == i && l == j) {
                    continue;
                }
                if (matrix[k][l] == 'o') {
                    *count += 1;
                }
            }
        }
        for (int o = j - 1; o < j + 2; o++) {
            if (matrix[0][o] == 'o') {
                *count += 1;
            }
        }
    }
}

void check_2_vertical(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    *count = 0;
    if (WIDTH - 1 - j > j) {
        for (int k = i - 1; k < i + 2; k++) {
            for (int l = j; l < j + 2; l++) {
                if (k == i && l == j) {
                    continue;
                }
                if (matrix[k][l] == 'o') {
                    *count += 1;
                }
            }
        }
        for (int o = i - 1 ; o < i + 2; o++) {
            if (matrix[o][WIDTH - 1] == 'o') {
                *count += 1;
            }
        }
    } else {
        for (int k = i - 1; k < i + 2; k++) {
            for (int l = j - 1; l < j + 1; l++) {
                if (k == i && l == j) {
                    continue;
                }
                if (matrix[k][l] == 'o') {
                    *count += 1;
                }
            }
        }
        for (int o = i - 1; o < i + 2; o++) {
            if (matrix[o][0] == 'o') {
                *count += 1;
            }
        }
    }
}

void check_corner_left_high(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    for (int k = i; k < i + 2; k++) {
        for (int l = j; l < j + 2 ; l++) {
            if (k == i && l == j) {
                continue;
            }
            *count = (matrix[k][l] == 'o') ? *count + 1 : *count;
        }
    }
    for (int o = j; o < j + 2; o++) {
        *count = (matrix[HEIGHT - 1 - i][o] == 'o') ? *count + 1 : *count;
    }
    for (int p = i; p < i + 2; p++) {
        *count = (matrix[p][WIDTH - 1 - j] == 'o') ? *count + 1 : *count;
    }
    *count = (matrix[HEIGHT - 1][WIDTH - 1] == 'o') ? *count + 1 : *count;
}

void check_corner_right_high(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    for (int k = i; k < i + 2; k++) {
        for (int l = j - 1; l < j + 1 ; l++) {
            if (k == i && l == j) {
                continue;
            }
            *count = (matrix[k][l] == 'o') ? *count + 1 : *count;
        }
    }
    for (int o = j - 1; o < j + 1; o++) {
        *count = (matrix[HEIGHT - 1 - i][o] == 'o') ? *count + 1 : *count;
    }
    for (int p = i; p < i + 2; p++) {
        *count = (matrix[p][WIDTH - 1 - j] == 'o') ? *count + 1 : *count;
    }
    *count = (matrix[HEIGHT - 1][0] == 'o') ? *count + 1 : *count;
}

void check_corner_left_bottom(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    for (int k = i - 1; k < i + 1; k++) {
        for (int l = j; l < j + 2 ; l++) {
            if (k == i && l == j) {
                continue;
            }
            *count = (matrix[k][l] == 'o') ? *count + 1 : *count;
        }
    }
    for (int o = j; o < j + 2; o++) {
        *count = (matrix[HEIGHT - 1 - i][o] == 'o') ? *count + 1 : *count;
    }
    for (int p = i - 1; p < i + 1; p++) {
        *count = (matrix[p][WIDTH - 1 - j] == 'o') ? *count + 1 : *count;
    }
    *count = (matrix[0][WIDTH - 1] == 'o') ? *count + 1 : *count;
}

void check_corner_right_bottom(char matrix[HEIGHT][WIDTH], int i, int j, int *count) {
    for (int k = i - 1; k < i + 1; k++) {
        for (int l = j - 1; l < j + 1 ; l++) {
            if (k == i && l == j) {
                continue;
            }
            *count = (matrix[k][l] == 'o') ? *count + 1 : *count;
        }
    }
    for (int o = j - 1; o < j + 1; o++) {
        *count = (matrix[HEIGHT - 1 - i][o] == 'o') ? *count + 1 : *count;
    }
    for (int p = i - 1; p < i + 1; p++) {
        *count = (matrix[p][WIDTH - 1 - j] == 'o') ? *count + 1 : *count;
    }
    *count = (matrix[0][0] == 'o') ? *count + 1 : *count;
}
