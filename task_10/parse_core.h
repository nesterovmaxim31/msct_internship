#pragma once

#include <stdio.h>
#include <stdlib.h>

// Типы объекта
typedef enum types {variable, expression, carrier} obj_type;

// Операторы
enum operators {FIRST, AND, OR, NOT, AND_NOT, OR_NOT};

// Структура данных для объекта
typedef struct object {
    // Показывает тип объекта
    obj_type type;
    // В случае, если новый объект - перменная, установим её индекс
    char variable_index; 
    // Устанавливает операцию, которуб надо выполнить
    enum operators operation;
    // Показывает уровень объекта
    size_t level;
    // Показывает количество составляющий
    size_t number_of_components;
    // Указавыет на массив значений данного объекта
    int* values;
    // Указатель на компоненты
    struct object** components;
} obj_t;

// Структура данных для переменных
struct variable_status_struct {
    size_t amount_of_variables;
    char* variables;
};

void* variable_status(int status, char new_var);

size_t get_boolean_expression(obj_t* current_obj, char* text, size_t index, size_t text_leght);