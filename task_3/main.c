#include "sort_core.h"


int main(int argc, char** argv) {
    // Вызываем функция sort_file передав в качества аргумента аргументы программы
    sort_file(argv[1], argv[2], argv[3]);
    return 0;
}