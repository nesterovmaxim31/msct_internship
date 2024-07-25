#include "stat_call.h"


int main(int argc, char** argv) {
    // Передаёт название файла из командной строки
    get_file_info(argv[1]);
    return 0;
}