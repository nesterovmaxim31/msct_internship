#include "chat.h"

// Отправляем сообщение процессу номер 2
void send_request(int file_descriptor, char *message, size_t message_leght) {
    write(file_descriptor, message, message_leght);
}

// Функция, которая возвращает срез данной строки с нулевого индекса до данного
char* get_proper_string(char* message, size_t lenght) {
    char* ans = (char*)malloc(lenght);
    for (size_t i = 0; i < lenght; i++) {
        ans[i] = message[i];
    }
    return ans;
}

// Функция, которая запускает процесс общения между процессами
void start_chat(const char *path_to_named_pipe_in, const char *path_to_named_pipe_out) {
    // Создаём именованный канал
    mkfifo(path_to_named_pipe_in, 0666);
    mkfifo(path_to_named_pipe_out, 0666);
    // Создаём переменную для хранения и передачи файлового дескприптора c read/write access mode
    int out_file_descriptor = open(path_to_named_pipe_out, O_WRONLY),
    in_file_descriptor = open(path_to_named_pipe_in, O_RDONLY);
    // Запускаем цикл который будет постоянно генерировать рандомные числа и отправлять их второму процессу
    char message_receiving[100], message_departure[100];
    // Функция read из unistd.h читаем из файлового дескпритора и возвращает количество прочитанный симполов
    ssize_t message_lenght;
    int some_random_number;
    while (TRUE) {
        // Генерируем рандомное число
        some_random_number = rand() % 10000;
        // Формируем строку из него
        sprintf(message_departure, "%d", some_random_number);
        printf("Отправка процессу 2 следующего числа для возведения в квадрат: %s\n", message_departure);
        // Отправление запроса по одному именованному каналу
        send_request(out_file_descriptor, message_departure, strlen(message_departure) + 5);
        // Получение ответа по другому
        message_lenght = read(in_file_descriptor, message_receiving, 100);
        // Парсить полученную строку
        // Вывод полученного ответа в консоль
        printf("От процесса два получено данное сообщение: %s\n", get_proper_string(message_receiving, message_lenght));
        // Для удобства анализа выводимых результатов утсановлна задержка
        sleep(2);
    }
}