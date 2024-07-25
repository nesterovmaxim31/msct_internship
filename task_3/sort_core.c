#include "sort_core.h"

// Выводит отсортированные данные в файл и на экран
void output_data(const char* target_file, char** text, size_t lines_number) {
    FILE *file_w;
    file_w = fopen(target_file, "w");
    for (size_t i = 0; i < lines_number; i++) {
        if (text[i] != NULL) {
            printf("%s", text[i]);
            fputs(text[i], file_w);
        }   
    }
    fclose(file_w);
}

// Удаляет пустые строки без видимых символов
void delete_unseen_lines(char** text, size_t lines_number) {
    // Переменная, показывающая найден ли видимый символ в обрабатываемой строке
    int visible_symbol_found = 0;
    for (size_t i = 0; i < lines_number; i++) {
        visible_symbol_found = 0;
        for (size_t j = 0; j < strlen(text[i]); j++) {
            if (text[i][j] >= 33) {
                visible_symbol_found = 1;
            }
        }
        if (!visible_symbol_found) text[i] = NULL;
    }
}

// Функция, которая сортирует строки в зависимости от их длины
void sort_by_lenght(char** text, size_t lines_number, int reverse) {
    char* temp;
    // Сортировка пузырьком
    for (size_t i = 0; i < lines_number - 1; i++) {
        for (size_t j = 0; j < lines_number - i - 1; j++) {
            if (!reverse && compare_leght_string(text[j], text[j + 1])) {
                temp = text[j];
                text[j] = text[j + 1];
                text[j + 1] = temp;
            } 
            else if (reverse && !compare_leght_string(text[j], text[j + 1])){
                temp = text[j];
                text[j] = text[j + 1];
                text[j + 1] = temp;
            }
        }
    }
}

// Функция, которая сортирует строки по алфавиту (с учётом регистра)
void sort_alphabetical(char** text, size_t lines_number, int reverse) {
    char* temp;
    for (size_t i = 0; i < lines_number - 1; i++) {
        for (size_t j = 0; j < lines_number - i - 1; j++) {
            if (reverse && compare_letters_string(text[j], text[j + 1])) {
                temp = text[j];
                text[j] = text[j + 1];
                text[j + 1] = temp;
            } 
            else if (!reverse && !compare_letters_string(text[j], text[j + 1])){
                temp = text[j];
                text[j] = text[j + 1];
                text[j + 1] = temp;
            }
        }
    }
}

// Функция, которая рандомно перемещает строки 
void sort_randomly(char** text, size_t lines_number) {
    char* temp;
    int random_value;
    for (size_t i = 0; i < lines_number; i++) {
        random_value = rand() % lines_number;
        temp = text[random_value];
        text[random_value] = text[lines_number - random_value - 1];
        text[lines_number - random_value - 1] = temp;
    }
}

// Функция, которая возвращает индекс метода сортировки
int get_sort_method_index(const char* proposed_sort_method) {
    // Методы сортировки
    // long_to_short - Сортировка строк по длине (Сначала длинные, потом короткие)
    // short_to_long - Сортировка строк по длине (Сначала короткие, потом длинные)
    // alphabetically - Сортировка строк по алфавиту (Начиная с a до Z)
    // antialphabetically - Сортировка строк по алфавиту (Начиная с Z до a)
    // random_mix - рандомное перемещние строк
    const char* sort_method_list[] = {"long_to_short", "short_to_long", "alphabetically", "antialphabetically", "random_mix"};
    for (size_t i = 0; i < 5; i++) {
        if (!strcmp(proposed_sort_method, sort_method_list[i])) {
            return i;
        }
    }
    return -1;
}

// Функция для получения количества строк в файле
size_t get_amout_of_lines(const char *source_file) {
    size_t ans = 1;
    FILE *file_r, *file_w;
    file_r = fopen(source_file, "r");
    while (!feof(file_r)) {
        if (getc(file_r) == '\n') ans++;
    }
    fclose(file_r);
    return ans;
}

// Функция, сортирующая файл
void sort_file(const char *source_file, const char *target_file, const char *proposed_sort_method) {
    FILE *file_r;
    // Открываем файл
    file_r = fopen(source_file, "r");
    // Проверка на существование указанного файла
    if (file_r == NULL) {
        printf("Файла %s не существует\n", source_file);
        return;
    }
    // Количество строк в файле
    size_t lines_number = get_amout_of_lines(source_file), line_lenght, i = 0;
    char *buffer, **text;
    // Выделяем память для хранения строк всего файла
    text = (char**)malloc(8 * lines_number);
    while (!feof(file_r)) {
        buffer = NULL;
        getline(&buffer, &line_lenght,file_r);
        // Выделяем память для каждой строки
        text[i] = (char*)malloc(line_lenght);
        // Копируем значения полученной строки в основной массив для обработки
        strcpy(text[i], buffer);
        // Освобождаем память выделенную getline для buffer
        free(buffer);
        i++;
    }
    // Добавим в конец последней строки знак переноса \n с целью избежать некорректного вывода результата
    strcat(text[lines_number - 1], "\n");
    fclose(file_r);
    // Сортировка
    // Получаем номер того способа, которым надо отсортировать строки файла
    int sort_method_index = get_sort_method_index(proposed_sort_method);
    //
    switch (sort_method_index) {
        case -1:
            puts("Введённого вами метода сортировки не предусмотрено в программе");
            return;
        case 0:
            sort_by_lenght(text, lines_number, 0);
            break;
        case 1:
            sort_by_lenght(text, lines_number, 1);
            break;
        case 2:
            sort_alphabetical(text, lines_number,  0);
            break;
        case 3:
            sort_alphabetical(text, lines_number,  1);
            break;
        case 4:
            sort_randomly(text,lines_number);
            break;
    }
    // Удаления строк без видимых символов
    delete_unseen_lines(text, lines_number);
    // Вывод отсортированных данных в выходной файл и в консоль
    output_data(target_file, text, lines_number);
}