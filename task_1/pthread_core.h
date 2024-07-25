#pragma once

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "merge_sort.h"
#include "secondary_functions.h"

// Различные состояния процесса. not_init - не начат, at_work - в работе, finished - работу закончил
typedef enum {not_init, at_work, finished} status;

typedef struct thread_data{
    // Указатель на сортируемый массив
    long* array;
    // Указатель на вспомогательный массив
    long* supporting_array;
    // Размер массива
    size_t size_of_array;
    // Номер каждого потока
    size_t index;
    // Текущий статус
    status current_status;
    // Указатель  на общий массив 
    struct thread_data* pointer_to_arg;
    // Индексы конца и начало кусочка
    size_t left_index, right_index;
    // Количество кусочков
    size_t amout_of_pieces;
} data_t;

void split_and_sort_array(long* array, size_t size_of_array, size_t number_of_threads);