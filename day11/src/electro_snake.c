#include <stdio.h>
#include <stdlib.h>

/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);

int input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);


void main()
{
    int is, js;
    int **matrix, **result;
    char c;
    if (scanf("%d%c", is, &c) == 0 || (c != ' ' && c != '\n') || is <= 0) {
        printf("n/a");
        return 0;
    }
    if (scanf("%d%c", js, &c) == 0 || (c != ' ' && c != '\n') || js <= 0) {
        printf("n/a");
        return  0;
    }
 

    input(matrix, &is,&js);

    
    sort_vertical(matrix, is, js, result);
    output(result,is,js);

    free(result[0]);
    free(result);
    
    sort_horizontal(matrix, is, js, result);
    output(result,is,js);
    free(result[0]);
    free(result);
    free(matrix[0]);
    free(matrix);
}


int input(int **matrix, int *n, int *m) {
    int control;
    matrix = (int**)malloc(*n * sizeof(int*));
    int* matrix1 = (int*)malloc(*n * *m * sizeof(int));

    for (int i = 0; i < *n; i++) {
        matrix[i] = &matrix1[i * *m];
    }
    if ((control = inputMatrix_spec4(matrix, *n, *m)) != 1) {
        control = 0;
    }

    return control;
}

void output(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

// Функция для сортировки матрицы по вертикали (змейкой)
void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    // Выделение памяти для результирующей матрицы
    *result_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        (*result_matrix)[i] = (int *)malloc(m * sizeof(int));
    }

    // Копирование элементов из исходной матрицы во временный одномерный массив
    int *temp_array = (int *)malloc(n * m * sizeof(int));
    int index = 0;
    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) { // Четный столбец
            for (int i = 0; i < n; i++) {
                temp_array[index++] = matrix[i][j];
            }
        } else { // Нечетный столбец
            for (int i = n - 1; i >= 0; i--) {
                temp_array[index++] = matrix[i][j];
            }
        }
    }
    int IsSorted = 0;
    while(IsSorted != 1){
    // Сортировка временного массива
    for (int i = 0; i < n * m - 1; i++) {
        for (int j = 0; j < n * m - i - 1; j++) {
            if (temp_array[j] > temp_array[j + 1]) {
                int temp = temp_array[j];
                temp_array[j] = temp_array[j + 1];
                temp_array[j + 1] = temp;
            }
        }
    }
    IsSorted = 1;
    // Проверка временного массива
    for (int i = 0; (i < n * m - 1) && IsSorted == 1; i++) {
        for (int j = 0; (j < n * m - i - 1) && IsSorted == 1; j++) {
            if (temp_array[j] > temp_array[j + 1]) {
                IsSorted = 0;
            }

        }
    }

    }

    // Копирование отсортированных элементов из временного массива в результирующую матрицу
    index = 0;
    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) { // Четный столбец
            for (int i = 0; i < n; i++) {
                result_matrix[i][j] = temp_array[index++];
            }
        } else { // Нечетный столбец
            for (int i = n - 1; i >= 0; i--) {
                result_matrix[i][j] = temp_array[index++];
            }
        }
    }

    // Освобождение памяти, занятой временным массивом
    free(temp_array);
}

// Функция для сортировки матрицы по горизонтали (змейкой)
void sort_horizontal(int **matrix, int n, int m, int **result_matrix) {
    // Выделение памяти для результирующей матрицы
    *result_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        (*result_matrix)[i] = (int *)malloc(m * sizeof(int));
    }

    // Копирование элементов из исходной матрицы во временный одномерный массив
    int *temp_array = (int *)malloc(n * m * sizeof(int));
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) { // Четная строка
            for (int j = 0; j < m; j++) {
                temp_array[index++] = matrix[i][j];
            }
        } else { // Нечетная строка
            for (int j = m - 1; j >= 0; j--) {
                temp_array[index++] = matrix[i][j];
            }
        }
    }

    // Сортировка временного массива
    for (int i = 0; i < n * m - 1; i++) {
        for (int j = 0; j < n * m - i - 1; j++) {
            if (temp_array[j] > temp_array[j + 1]) {
                int temp = temp_array[j];
                temp_array[j] = temp_array[j + 1];
                temp_array[j + 1] = temp;
            }
        }
    }

    // Копирование отсортированных элементов из временного массива в результирующую матрицу
    index = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) { // Четная строка
            for (int j = 0; j < m; j++) {
                result_matrix[i][j] = temp_array[index++];
            }
        } else { // Нечетная строка
            for (int j = m - 1; j >= 0; j--) {
                result_matrix[i][j] = temp_array[index++];
            }
        }
    }

    // Освобождение памяти, занятой временным массивом
    free(temp_array);
}