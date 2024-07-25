#include "rmdir_call.h"

// Выбранный системный вызов - rmdir
int main() {
    // Чтобы появилась ошибка, выберем не пустую директорию
    const char* path = "./some_dir";
    call_rmdir(path);
    return 0;
}