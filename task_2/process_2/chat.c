#include "chat.h"

// Отправляем сообщение процессу номер 1
void send_request(int file_descriptor, char *message, size_t message_leght) {
    write(file_descriptor, message, message_leght);
}

// Получает и обрабатывает запрос. После Отправляет ответ черех send_request
void answer_request(int file_descriptor, char *message, size_t message_lenght) {
    // action содержит ключевое слово для выполнение процесса square, answer будет содержать ответ  
    char* action, *answer;
    action = (char*)malloc(message_lenght);
    answer = (char*)malloc(message_lenght * message_lenght);
    int number;
    size_t answer_leght;
    // Парсим строку
    printf("От процесса №1 получено данное число: %s\n", message);
    size_t leght_of_parsed_string = sscanf(message, "%d", &number);
    answer_leght = sprintf(answer, "%d\n", squaring_number(number));
    // Отправление запроса с ответом
    send_request(file_descriptor, answer, strlen(answer));
    // Освобождение памяти выделенной для переменных
    free(action);
    free(answer);
}

// Функция, которая запускает процесс общения между процессами
void start_chat(const char *path_to_named_pipe_in, const char *path_to_named_pipe_out) {
    // Создаём именованный канал
    mkfifo(path_to_named_pipe_in, 0666);
    mkfifo(path_to_named_pipe_out, 0666);
    // Создаём переменную для хранения и передачи файлового дескприптора c read/write access mode
    int in_file_descriptor = open(path_to_named_pipe_in, O_RDONLY),
    out_file_descriptor = open(path_to_named_pipe_out, O_WRONLY);
    // Переменная для хранения полученного значения
    char message_receiving[100];
    // Функция read из unistd.h читаем из файлового дескпритора и возвращает количество прочитанный симполов
    ssize_t message_lenght;
    // Запускаем цикл который будет постоянно читать именованный канал
    while (TRUE) {
        // Считываем из первого именованного канала число, которое надо возвести в квадрат
        message_lenght = read(in_file_descriptor, message_receiving, 100);
        // После считывания, отправляем полученное сообщение на обработку
        answer_request(out_file_descriptor, message_receiving, strlen(message_receiving) + 1);
    }
}