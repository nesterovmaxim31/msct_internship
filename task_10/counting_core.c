#include "counting_core.h"
#include "parse_core.h"

// Выводит результирующие значения
void output_answer(int* variable_values, int** truth_table) {
    struct variable_status_struct* current = variable_status(0, '\0');
    puts("Значения переменных и выражения:");
    // Выводим все переменные
    for(size_t i = 0; i < current -> amount_of_variables; i++) {
        printf("\t%c", current -> variables[i]);
    }
    printf("\tF\n");
    // Выводим таблицу истинности под перменными и значения выражения под F
    for(size_t j = 0; j < pow(2, current -> amount_of_variables); j++) {
        for(size_t k = 0; k < current -> amount_of_variables; k++) {
            printf("\t%d", truth_table[j][k]);
        }
        printf("\t%d\n", variable_values[j]);
    }
}

// Функция, генерирующая таблицу истинности в зависимости от количества переменных
int **generate_truth_table() {
    // Получаем из функции variable_status количество неповторяющихся переменных
    struct variable_status_struct* current = variable_status(0, '\0');
    size_t amount_of_variables = current -> amount_of_variables;
    size_t amount_of_rows = pow(2, amount_of_variables);
    int **truth_table;
    truth_table = (int**)malloc(8 * amount_of_rows);
    truth_table[0] = calloc(amount_of_variables, sizeof(int));
    for (size_t i = 1; i < amount_of_rows; i++) {
        truth_table[i] = (int*)malloc(amount_of_variables * sizeof(int));
        memcpy(truth_table[i], truth_table[i - 1], sizeof(int) * amount_of_variables);
        for (size_t j = amount_of_variables - 1; j >= 0; j--) {
            // Добавляем каждый раз единику, учитывая, что работает в двоичной системе счисления
            if (truth_table[i][j] == 0) {
                truth_table[i][j] = 1;
                break;
            } else {
                truth_table[i][j] = 0;
            }
        }
    }
    return truth_table;
}

// Функция, которая находит из таблицы истинности нужный столбец для переменной
int* get_variable_value(int** truth_table, char var) {
    int* ans;
    size_t variable_index;
    struct variable_status_struct* current = variable_status(0, '\0');
    // Находим индекс переменной
    for (size_t i = 0; i < current -> amount_of_variables; i++) {
        if (current -> variables[i] == var) {
            variable_index = i;
        }
    }
    // Находим значения из таблицы истинности 
    ans = (int*)malloc(sizeof(int) * pow(2, current -> amount_of_variables));
    for (size_t j = 0; j < pow(2, current -> amount_of_variables); j++) {
        ans[j] = truth_table[j][variable_index];
    }
    return ans;
}

// Функция, которая вычисляет значения при взаимодействии двух объектов, и помещает ответ во второй аргумент
void get_pair_value (int* first_variable_values, int* second_variable_values, enum operators operation, enum operators first_operator) {
    struct variable_status_struct* current = variable_status(0, '\0');
    for (size_t i = 0; i < pow(2, current -> amount_of_variables); i++) {
        if (operation == AND && first_operator != NOT) {
            second_variable_values[i] = (first_variable_values[i] && second_variable_values[i]);
        }
        else if(operation == AND && first_operator == NOT) {
            second_variable_values[i] = (!first_variable_values[i] && second_variable_values[i]);
        }

        else if (operation == OR && first_operator != NOT) {
            second_variable_values[i] = (first_variable_values[i] || second_variable_values[i]);
        }
        else if (operation == OR && first_operator == NOT) {
            second_variable_values[i] = (!first_variable_values[i] || second_variable_values[i]);
        }
        
        else if (operation == AND_NOT && first_operator != NOT) {
            second_variable_values[i] = (first_variable_values[i] && !second_variable_values[i]);
        }
        else if (operation == AND_NOT && first_operator == NOT) {
            second_variable_values[i] = (!first_variable_values[i] && !second_variable_values[i]);
        }

        else if (operation == OR_NOT && first_operator != NOT) {
            second_variable_values[i] = (first_variable_values[i] || !second_variable_values[i]);
        }
        else if (operation == OR_NOT && first_operator == NOT) {
            second_variable_values[i] = (!first_variable_values[i] || !second_variable_values[i]);
        }
    }
}

// Функция, которая меняет значения двоичного массива на противоположные  
void reverse_values(int* variable_values) {
    struct variable_status_struct* current = variable_status(0, '\0');
    for (size_t i = 0; i < pow(2, current -> amount_of_variables); i++) {
        if (variable_values[i]) variable_values[i] = 0;
        else variable_values[i] = 1;
    }
}

// Функция, которая высчитывает значение выражения
int* get_expression_values(obj_t* current_obj, int** truth_table) {
    // Случай при котором один подчинённый объект и это переменная
    if (current_obj -> number_of_components == 1 && current_obj -> components[0] -> type == variable ) {
        int *temp = get_variable_value(truth_table, current_obj -> components[0] -> variable_index);
        if (current_obj -> components[0] -> operation == NOT) {
            reverse_values(temp);
        }
        return temp;
    } 
    // Случай при котором один подчинённый объект и это выражение
    else if (current_obj -> number_of_components == 1 && current_obj -> components[0] -> type == expression) {
        if (current_obj -> components[0] -> operation == NOT) {
            current_obj -> components[0] -> values = get_expression_values(current_obj -> components[0], truth_table);
            reverse_values(current_obj -> components[0] -> values);
        } else {
            current_obj -> components[0] -> values = get_expression_values(current_obj -> components[0], truth_table);
        }
        
        return current_obj -> components[0] -> values;
    }
    // Случаи, когда подчинённых объектов 2 и более
    else {
        for (size_t i = 0; i < (current_obj -> number_of_components - 1); i++) {
            // Обрабатываем первый объект из пары в зависимости от его типа
            if (current_obj -> components[i] -> type == variable) {
                current_obj -> components[i] -> values = get_variable_value(truth_table, current_obj -> components[i] -> variable_index);
            } 
            else if (current_obj -> components[i] -> type == expression){
                current_obj -> components[i] -> values = get_expression_values(current_obj -> components[i], truth_table);
            }
            // Обрабатываем второй объект из пары в зависимости от его типа
            if (current_obj -> components[i + 1] -> type == variable) {
                current_obj -> components[i + 1] -> values = get_variable_value(truth_table, current_obj -> components[i + 1] -> variable_index);
            } 
            else if (current_obj -> components[i + 1] -> type == expression){
                current_obj -> components[i + 1] -> values = get_expression_values(current_obj -> components[i + 1], truth_table);
            }
            // Получение значения при взаимодействии двух рассматриваемых объектов
            get_pair_value(current_obj -> components[i] -> values, current_obj -> components[i + 1] -> values,
             current_obj -> components[i + 1] -> operation, current_obj -> components[i] -> operation);
            // Меняем тип данного объекта на 'носитель - carrier'. Он показывает, что данный объект 
            // уже готов к следующей операции и не требует обработки (как переменная или выражение)
            current_obj -> components[i + 1] -> type = carrier;
        }
        // Объект обработан
        return current_obj -> components[current_obj -> number_of_components - 1] -> values;
    }
}


void handle_expression(obj_t* expr) {
    // Создаём таблицу истинности
    int** truth_table = generate_truth_table();
    // Вызываем функцию, для вычисления значений
    expr -> values = get_expression_values(expr, truth_table);
    // Выводим результат
    output_answer(expr -> values, truth_table);
}
