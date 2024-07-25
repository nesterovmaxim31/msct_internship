#include "stat_call.h"

// Функция, которая запускает отдельно пользовательскую команду для получения имени пользователя
void get_user_name(int id) {
    FILE *pf;
    char command[100];
    char data[100];
    sprintf(command, "id -nu %d", id); 
    // Создаём новый поток, в него вводим команду (строка command)
    pf = popen(command,"r"); 
    // Считываем из потока ответ от компьютера 
    fgets(data, 100 , pf);
    printf("Имя пользователя, создавшего файл: %s", data);
    fclose(pf);
}

// Функция которая из количества секунд делает строку, с привычным представлением времени
char* get_familiar_look_time(time_t rawtime) {
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    return asctime(timeinfo);
} 

// Функция для получения информации о файле
void get_file_info(char* path) {
    // Создаём переменную содержащую скртуру данных stat
    struct stat file_data;
    // Вызываем функцию stat
    stat(path, &file_data);
    // Проверка, что данный файл существует
    if (errno) {
        perror("Ошибка stat");
        return;
    }
    // Получим информацию о типе файла с помощью битовой маски S_IFMT
    switch (file_data.st_mode & S_IFMT) {
        // Пользуемся костантами из sys/stat.h
        case S_IFREG:
            puts("Это обычный файл");
            break;
        case S_IFDIR: 
            puts("Это каталог");
            break;
        case S_IFCHR:
            puts("Это байт-ориентированный файл");
            break;
        case S_IFBLK:
            puts("Это блок-ориентированный файл");
            break;
    }
    // Вывод иной справочной информации
    printf("ID пользователя, создавшего файл: %d\n", file_data.st_uid);
    get_user_name(file_data.st_uid);
    printf("Размер файла в байтах: %lu\n", file_data.st_size);
    printf("Время последнего открытия файла: %s", get_familiar_look_time(file_data.st_atim.tv_sec));
    printf("Время последнего изменения файла: %s",  get_familiar_look_time(file_data.st_mtim.tv_sec));
}