#include "parse_line.h"

// Проверка на повторение
int repetition_check(char** correct_options, size_t number_of_correct_options, char* new_possible_option) {
    for (size_t i = 0; i < number_of_correct_options; i++) {
        if (!memcmp(correct_options[i], new_possible_option, strlen(new_possible_option))) {
            return 0;
        }
    }
    return 1;
}

// Создание характеристического вектора
int*  create_characteristic_vector(size_t size) {
    int* vector = (int*)malloc(sizeof(int) * size);
    for (size_t i = 1; i < size; i++) {
        vector[i] = 0;
    }
    return vector;
}

// Проверяет правильность аргумента у опции --elbrus
int check_elbrus_arguments(char* argument) {
    const char* possible_arguments[] = {"1c+", "2c+",  "2c3",  "4c",  "8c",  "16c"};
    for (size_t i = 0; i < 6; i++) {
        if (!memcmp(argument, possible_arguments[i], strlen(possible_arguments[i]))) {
            return 1;
        }
    }
    return 0;
}

//Если опции правльны, то вывод ответа осуществляет данная функция
void output_answer(char** correct_options, size_t number_of_correct_options,  char** argv, int* characteristic_vector, size_t size) {
    // Выводим правильын опции
    printf("Options are correct: ");
    for(size_t i = 0; i < number_of_correct_options; i++) {
        printf("%s, ", correct_options[i]);
    }
    // Выыводимм не опции
    printf("non-options: ");
    // Для корректности вывода создём перменную, которая отслеживает номер вывода
    int is_first = 1;
    for(size_t i = 1; i < size; i++) {
        if (characteristic_vector[i] == 0 && is_first) {
            printf("%s", argv[i]);
            is_first = 0;
        } 
        else if (characteristic_vector[i] == 0) {
            printf(", %s", argv[i]);
        }
    }
    puts("."); 
}


int handle_option(int getopt_returned_value, char** correct_options, size_t* number_of_correct_options, char* optarg) {
    switch (getopt_returned_value) {
        // Если -2, значит дана опция --elbrus с некоторым аргументов
        case -2:
            // Проверим, является ли аргумент допустимым
            if (check_elbrus_arguments(optarg)) {
                correct_options[*number_of_correct_options] = (char*)malloc(11);
                char double_option[11];
                sprintf(double_option, "elbrus=%s", optarg);
                if (repetition_check(correct_options, *number_of_correct_options, double_option)) {
                    strcpy(correct_options[*number_of_correct_options], double_option);
                    (*number_of_correct_options)++;
                }
                return 1;
            }
            return -1;
            break;
        // Описываем все 4 короткие опции
        case 'm': 
            if (repetition_check(correct_options, *number_of_correct_options, "m")) {
                correct_options[*number_of_correct_options] = (char*)malloc(1);
                *correct_options[*number_of_correct_options] = 'm';
                (*number_of_correct_options)++;
            }
            break;

        case 'c': 
            if (repetition_check(correct_options, *number_of_correct_options, "c")) {
                correct_options[*number_of_correct_options] = (char*)malloc(1);
                *correct_options[*number_of_correct_options] = 'c';
                (*number_of_correct_options)++;
            }
            break;

        case 's': 
            if (repetition_check(correct_options, *number_of_correct_options, "s")) {
                correct_options[*number_of_correct_options] = (char*)malloc(1);
                *correct_options[*number_of_correct_options] = 's';
                (*number_of_correct_options)++;
            }
            break;

        case 't': 
            if (repetition_check(correct_options, *number_of_correct_options, "t")) {
                correct_options[*number_of_correct_options] = (char*)malloc(1);
                *correct_options[*number_of_correct_options] = 't';
                (*number_of_correct_options)++;
            }
            break;
        
        case '?':
            return 0;
    }
    return 1;
}

void parse_line(int argc, char** argv) {
    // Отключаем вывод ошибки
    opterr = 0;
    // обрабатываем опцию --elbrus
    const struct option data[] = {{"elbrus", 1, NULL, -2}, {0, 0, 0, 0}};    
    // Хранит адреса строк, содержащие наименования правильных опций
    char** correct_options;
    correct_options = (char**)malloc(sizeof(char*) * (argc - 1));
    // Хранит количество опций
    size_t number_of_correct_options = 0;
    // Хранит какой индекс опции в argv что значит, 0 - non_option, 1 - option
    int* characteristic_vector = create_characteristic_vector(argc);
    // Переменная для хранения полученного значения от getopt_long
    int getopt_returned_value, is_correct;
    // Создаётся копия argv, так как getopt перемещает содержимое argv при работе
    char** copy_argv = (char**)malloc(8 * argc);
    memcpy(copy_argv, argv, 8 * argc);
    while ((getopt_returned_value = getopt_long(argc, copy_argv, "mcst", data, NULL)) != -1) {
        is_correct = handle_option(getopt_returned_value, correct_options, &number_of_correct_options, optarg);
        if (is_correct == 0) {
            printf("Options are incorrect: -%c\n", optopt);
            return;
        }
        else if (is_correct == -1) {
            printf("Options for --elbrus is incorrect: %s\n", optarg);
            return;
        }
        characteristic_vector[optind - 1] = 1;
    }
    output_answer(correct_options, number_of_correct_options, argv, characteristic_vector, argc);
}