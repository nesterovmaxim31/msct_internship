#include "process_control.h"


int main(int argc, char** argv) {
    // Создаём параллельный процесс
    int parallel_process_pid = fork();
    copy_to_new_file(argv[1], parallel_process_pid);
    // Ждём пока выполнится порождённый процесс. Если рассматриваемый процесс
    // является порождённым, то parallel_process_pid = 0
    if (parallel_process_pid) {
        waitpid(parallel_process_pid, NULL, 0);
    }
    // Если ошибка, то досрочно завершаем процесс
    if (errno) return 0;
    // Выводим в консоль содержимое файлов
    output_file_data(parallel_process_pid);
    return 0;
}