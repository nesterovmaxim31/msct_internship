#include "matrix.h"


int main() {
    // Создаём две рандомные матрицы размером 1000x1000 согласно условию
    int **matrix_1, **matrix_2, **matrix_result;
    matrix_1 = generate_matrix();
    matrix_2 = generate_matrix();
    matrix_result = generate_matrix();
    multiply_matrix(matrix_1, matrix_2, matrix_result);
    return 0;
}