#include "process_control.h"

// Функция для вывода содержимого каждого из файлов в консоль
void output_file_data(int fork_value) {
    FILE *file_r;
    // Случай, если рассматриваемый процесс является родительским
    if (fork_value) {
        file_r = fopen("parent_copy.txt", "r");
    }
    // Случай, если рассматриваемый процесс является порождённым 
    else {
        file_r = fopen("child_copy.txt", "r");
    }
    // Выводим в консоль содержимое файлов
    char c = getc(file_r);
    while (c != EOF) {
        printf("%c", c);
        c = getc(file_r);
    }
    fclose(file_r);
}

// Функция, которая запускает непосредственно процесс копирования с новый файл
void copy_to_new_file(const char* source_file, int fork_value) {
    FILE *file_r, *file_w;
    // Открываем файл для чтения и записи
    file_r = fopen(source_file, "r");
    if (errno) {
        perror("Ошибка fopen");
        return;
    }
    // Случай, если рассматриваемый процесс является родительским
    if (fork_value) {
        file_w = fopen("parent_copy.txt", "w");
    // Случай, если рассматриваемый процесс является порождённым
    } else {
        file_w = fopen("child_copy.txt", "w");
    }
    // Копирование в новый файл
    char c = getc(file_r);
    while (c != EOF) {
        putc(c, file_w);
        c = getc(file_r);
    }
    fclose(file_r);
    fclose(file_w);
}
