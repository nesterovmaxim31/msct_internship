#include "merge_sort.h"

// Стандартный алгоритм сортировки слиянием
// Обрабатывает отдельно взятые кусочки размером 'size_of_piece' из функции sort_array
void comparator(long* source_array, long* supporting_array, size_t last_index, 
                size_t left_index, size_t right_index) {
    size_t local_left_index = left_index, local_right_index = right_index;
     
    for (size_t i = left_index; i < last_index; i++) {
        if (local_left_index < right_index && (local_right_index >= last_index || 
                                                source_array[local_left_index] <= source_array[local_right_index])) {
            supporting_array[i] = source_array[local_left_index];
            local_left_index++;
        } else {
            supporting_array[i] = source_array[local_right_index];
            local_right_index++;    
        }
    } 
}

// Функция для сортировки массива методом слияния
void sort_array(long* source_array, long* supporting_array, size_t size_of_array) {
    // В данном цикле сначал весь массив разбивается на элементарные пары (по 2) и происходит сравнение
    // На следующем шаге массив разбивается уже по 4 элемента, происходит сравнение и сортировка и так далее
    for (size_t size_of_piece = 1; size_of_piece < size_of_array; size_of_piece *= 2) {
        for (size_t i = 0; i < size_of_array; i += size_of_piece * 2) {
            comparator(source_array, supporting_array, min_pair(i + size_of_piece * 2, size_of_array), 
            i, min_pair(i + size_of_piece, size_of_array));
        }
        memcpy(source_array, supporting_array, size_of_array * sizeof(long));
    }
    
}