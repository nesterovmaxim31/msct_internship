#include "matrix.h"
#include "signal_handler.h"
#include <signal.h>

// Выполняет одну итерацию умножения матриц
int multiply_row_by_column(int** matrix_1, int** matrix_2, size_t i, size_t j) {
    int ans = 0;
    for(size_t k = 0; k < 1000; k++) {
        ans += (matrix_1[i][k] * matrix_2[k][j]);
    }
    return ans;
}

// Функция для создания рандомной матрицы размеров 1000x1000
int** generate_matrix() {
    int** matrix;
    matrix = (int**)malloc(sizeof(int*) * 1000);
    for (size_t i = 0; i < 1000; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * 1000);
    }
    return matrix;
}

// Перемножение двух квадратных матриц размеров 1000x1000 с задержкой в 1 секунду
void multiply_matrix(int** matrix_1, int** matrix_2, int** matrix_result) {
    // Перменная отвечает за то, был ли уже хоть раз получен сигнал SIGINT
    int is_SIGINT_recieved = 0;
    // Изменяет реакцию на SIGINT на вызов функции sigint_hnd
    signal(SIGINT, sigint_hnd);
    for (size_t i = 0; i < 1000; i++) {
        for (size_t j = 0; j < 1000; j++) {
            matrix_result[i][j] = multiply_row_by_column(matrix_1, matrix_2, i, j);
            // Если количество полученных сигналов SIGINT равно 1, то выводим требуемую инфорацию
            if (change_get_current_status(0) == 1 && !is_SIGINT_recieved){
                is_SIGINT_recieved = 1;
                printf("Рассматриваемый столбец: %lu, рассматриваемая строка: %lu\n", j, i);
                // Меняем реакцию на SIGINT на реакцию по умолчанию
                signal(SIGINT, SIG_DFL);
            }
            sleep(1);
        }
    }
}