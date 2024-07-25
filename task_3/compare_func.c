#include "compare_func.h"

// Сравнивает длины двух строк
int compare_leght_string(const char* first_string, const char* second_string) {
    if (strlen(first_string) <= strlen(second_string)) {
        return 1;
    } else {
        return 0;
    }
}

// Функция для получения минимального значения из двух данных
int min_pair(int a, int b) {
    if (a >= b) return b;
    else return a;
}

// Сравнивает буквы по алфавиту двух строк
int compare_letters_string(const char* first_string, const char* second_string) {
    for (size_t i = 0; i < min_pair(strlen(first_string), strlen(second_string)); i++) {
        if (first_string[i] < second_string[i]) {
            return 1;
        } 
        else if (first_string[i] > second_string[i]) {
            return 0;
        }
    }
    return 0;
}