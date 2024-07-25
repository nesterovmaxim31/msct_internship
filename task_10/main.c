#include "counting_core.h"


int main() {
    // Создаём переменные для хранения логического выражения и его длины
    char* text = NULL;
    size_t text_leght;
    printf("Введите логическое выражение согласно правилам\n");
    // Вводим логичское выражение
    text_leght = getline(&text, &text_leght,stdin);
    // Создаём объект, который будет включать в себя все другие
    obj_t* expr;
    expr = (obj_t*)malloc(sizeof(obj_t)); 
    // Парсинг логического выражения 
    get_boolean_expression(expr, text, 0, text_leght);
    // Вычисления значения логического выражения
    handle_expression(expr);
    return 0;
}