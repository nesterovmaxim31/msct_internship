#include "signal_handler.h"

// Для либо для получения количества полученных сигналов SIGINT (при status = 0), 
// либо для увелечения счётчика на 1 (status = 1)
int change_get_current_status(int status) {
    // Перменная которая считает количество количество SIGINT 
    // Статическая, чтобы её значение не изменялось при множественных вызовах функции
    static size_t amout_of_receipt = 0;
    if (status) {
        amout_of_receipt++;
        return 0;
    } else {
        return amout_of_receipt;
    }
}

// Обработчик SIGINT
void sigint_hnd() {
    change_get_current_status(1);
}