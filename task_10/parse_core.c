#include "parse_core.h"

// Функция, которая хранит количество перменных и их названия
void* variable_status(int status, char new_var) {
    static struct variable_status_struct current = {0, NULL};
    if (status) {
        // Проверка на повторение
        for (size_t i = 0; i < current.amount_of_variables; i++) {
            if (current.variables[i] == new_var) return NULL; 
        }
        // Если повторений нет, то добавляем новую переменную
        current.amount_of_variables++;
        current.variables = realloc(current.variables, current.amount_of_variables);
        current.variables[current.amount_of_variables - 1] = new_var;
        return NULL;
    } else {
        return &current;
    }
}


size_t get_boolean_expression(obj_t* current_obj, char* text, size_t index, size_t text_leght) {
    current_obj -> number_of_components = 0;
    enum operators current_operator = FIRST;
    int NOT_flag = 0;
    size_t i = index;
    while (i < text_leght) {
        // Случай если при переборе встречается перменная
        if (text[i] <= 90 && text[i] >= 65 && 
        ((i + 1) == text_leght || text[i + 1] == ' ' || text[i + 1] == ')' || text[i + 1] == '\n')) {
            // Создаём новую перменную
            variable_status(1, text[i]);
            // Создаём новый объект типа перменная
            obj_t* new_var = (obj_t*)malloc(sizeof(obj_t));
            new_var -> type = variable;
            new_var -> level = current_obj -> level + 1;
            new_var -> operation = current_operator;
            new_var -> variable_index = text[i];
            // Увеличиваем количество подчинённых объектов данному на 1
            current_obj -> number_of_components++;
            current_obj -> components = realloc(current_obj -> components, sizeof(obj_t) * current_obj -> number_of_components);
            current_obj -> components[current_obj -> number_of_components - 1] = new_var;
            i++;
        }
        // Если встречается AND
        else if (text_leght - i >= 2 && text[i] == 'A' && text[i + 1] == 'N' && text[i + 2] == 'D') {
            current_operator = AND;
            i += 3;
        } 
        // Если встречается OR
        else if (text_leght - i >= 1 && text[i] == 'O' && text[i + 1] == 'R') {
            current_operator = OR;
            i += 2;
        }
        // Если встречается NOT
        else if (text_leght - i >= 2 && text[i] == 'N' && text[i + 1] == 'O' && text[i + 2] == 'T') {
            if (current_operator == AND) current_operator = AND_NOT;
            else if (current_operator == OR) current_operator = OR_NOT;
            else if (current_operator == FIRST) current_operator = NOT;
            i += 3;
        } 
        // Если встречается (, то создаём новый объект
        else if (text[i] == '(') {
            obj_t* new_obj = (obj_t*)malloc(sizeof(obj_t));
            new_obj -> type = expression;
            new_obj -> level = current_obj -> level + 1;
            new_obj -> operation = current_operator;
            // Увеличиваем количество подчинённых объектов данному на 1
            current_obj -> number_of_components++;
            current_obj -> components = realloc(current_obj -> components, sizeof(obj_t) * current_obj -> number_of_components);
            current_obj -> components[current_obj -> number_of_components - 1] = new_obj;
            i = get_boolean_expression(new_obj, text, i + 1, text_leght);
        }
        // Завершаем создание рассматриваемого объекта
        else if (text[i] == ')') {
            return i + 1;
        } 
        else {
            i++;
        }
    }
}