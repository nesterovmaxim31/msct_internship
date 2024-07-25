#include "chat.h"


int main()
{
    // Создаём переменные, содержащие адрес файла откуда данный процесс будет считывать информация (named_pipe_in)
    // и куда будет выводить информацию (named_pipe_out)
    const char  *path_to_named_pipe_in = "/tmp/fifo_file_1", *path_to_named_pipe_out = "/tmp/fifo_file_2";
    // Начинаем чат
    puts("Процесс №2\nЗапросы и ответы:");
    start_chat(path_to_named_pipe_in, path_to_named_pipe_out);
    return 0;
}