#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int staticMem(int is, int js);
int dinamicMem1(int** data, int rows, int cols);
int dinamicMem2(int** data, int rows, int cols);
int dinamicMem3(int** data, int rows, int cols);
int input_dano(int* mode, int* is, int* js);
int inputMatrix(int** matrix, int rows, int cols);
int inputMatrix_spec4(int** matrix, int rows, int cols);
void outputMatrix(int** matrix, int rows, int cols);

int main() {
    int mode;
    int is, js;
    int** matrix = NULL;

    if (input_dano(&mode, &is, &js) != 1 || (js <= 0 || js <= 0)) {
        printf("n/a");
        return 0;
    }
    switch (mode) {
        case 1: {
            if (is > NMAX || js > NMAX || staticMem(is, js) != 1) {
                printf("n/a");
                return 0;
            }
            break;
        }

        case 2: {
            if (dinamicMem1(matrix, is, js) != 1) {
                printf("n/a");
            }
            break;
        }
        case 3: {
            if (dinamicMem2(matrix, is, js) != 1) {
                printf("n/a");
            }
            break;
        }
        case 4: {
            if (dinamicMem3(matrix, is, js) != 1) {
                printf("n/a");
            }
            break;
        }
    }

    return 0;
}

int staticMem(int is, int js) {
    int data1[is][js];
    int control = 1;
    char c;
    printf("Задайте массив: \n");
    for (int i = 0; i < is && control == 1; i++) {
        for (int j = 0; j < js && control == 1; j++) {
            if (scanf("%d%c", &data1[i][j], &c) != 2 || (c != ' ' && c != '\n')) {
                control = 0;
            }
        }
    }
    for (int i = 0; i < is && control == 1; i++) {
        for (int j = 0; j < js; j++) {
            printf("%d", data1[i][j]);
            if (j < js - 1) {
                printf(" ");
            }
        }
        if (i < is - 1) {
            printf("\n");
        }
    }
    return control;
}

// Функция для выделения памяти под матрицу динамическим способом (по строкам)
int dinamicMem1(int** data, int rows, int cols) {
    int control;
    data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        data[i] = (int*)malloc(cols * sizeof(int));
    }
    if ((control = inputMatrix_spec4(data, rows, cols)) == 1) {
        outputMatrix(data, rows, cols);
    }
    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);
    return control;
}

// Функция для выделения памяти под матрицу динамическим способом (в виде одномерного массива)
int dinamicMem2(int** data, int rows, int cols) {
    int control;
    data = (int**)malloc(rows * sizeof(int*));
    int* matrix = (int*)malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        data[i] = &matrix[i * cols];
    }
    if ((control = inputMatrix_spec4(data, rows, cols)) == 1) {
        outputMatrix(data, rows, cols);
    }

    free(matrix);
    free(data);
    return control;
}

// Функция для выделения памяти под матрицу динамическим способом (в виде двумерного массива)
int dinamicMem3(int** data, int rows, int cols) {
    int control;
    data = malloc(rows * cols * sizeof(int) + rows * sizeof(int*));
    int* ptr = (int*)(data + rows);
    for (int i = 0; i < rows; i++) {
        data[i] = ptr + cols * i;
    }
    if ((control = inputMatrix_spec4(data, rows, cols)) == 1) {
        outputMatrix(data, rows, cols);
    }

    free(data);
    return control;
}

// Функция для ввода матрицы
int inputMatrix(int** matrix, int rows, int cols) {
    int control = 1;
    char c;
    printf("Задайте массив: \n");
    for (int i = 0; i < rows && control == 1; i++) {
        for (int j = 0; j < cols && control == 1; j++) {
            if (scanf("%d%c", &matrix[i][j], &c) != 2 || (c != ' ' && c != '\n')) {
                control = 0;
            }
        }
    }
    return control;
}

int inputMatrix_spec4(int** matrix, int rows, int cols) {
    int control = 1;
    int temp_var;
    char c;
    printf("Задайте массив: \n");
    for (int i = 0; i < rows && control == 1; i++) {
        for (int j = 0; j < cols && control == 1; j++) {
            if (scanf("%d%c", &temp_var, &c) != 2 || (c != ' ' && c != '\n')) {
                control = 0;
            }
            *(*(matrix + i) + j) = temp_var;
        }
    }
    return control;
}

int input_dano(int* mode, int* is, int* js) {
    char c;
    int res = 1;
    printf("Выберите способ выделения памяти:\n");
    printf("1. Статическое выделение памяти\n");
    printf("2. Динамическое выделение памяти в виде массива с массивами\n");
    printf("3. Динамическое выделение памяти в виде 2 массивов (массив указателей + массив элементов)\n");
    printf("4. Динамическое выделение памяти в виде одномерного массива\n");
    printf("Ваш выбор: ");
    scanf("%d%c", mode, &c);
    if (c != '\n') {
        return 0;
    }
    if (*mode <= 0 || *mode > 4) {
        return 0;
    }
    printf("Введите количество строк и столбцов матрицы (пример:2 2): ");
    if (scanf("%d%c", is, &c) == 0 || (c != ' ' && c != '\n')) {
        res = 0;
    }
    if (scanf("%d%c", js, &c) == 0 || (c != ' ' && c != '\n')) {
        res = 0;
    }
    return res;
}

// Функция для вывода матрицы
void outputMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) {
                printf(" ");
            }
        }
        if (i < rows - 1) {
            printf("\n");
        }
    }
}
