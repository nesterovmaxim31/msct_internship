#include "pthread_core.h"


// Если MANUAL_INPUT не 0, то ввод осуществляется вручную через консоль. 
// Если 0, то будет отсортирован некоторый рандомно сгенерированный массив 
#define MANUAL_INPUT 1

// Объявление количества потоков, которые будут задествованы для многопоточности
#define NUMBER_OF_THREADS 16


// Функция main
int main() {
    // Перменная для хранения размера массива
    size_t size_of_array;
    // Переменная для хранения адреса с обрабатываемым массивом
    long* array;
    if (MANUAL_INPUT) {
        puts("Введите размер сортируемого массива: ");
        // Ввод длины массива через консоль
        scanf("%lu", &size_of_array);
        // Выделения памяти под сортируемый массив
        array = (long*)malloc(sizeof(long) * size_of_array);
        // Ввод значений массива через консоль (Значения можно как писать построчно, так и в одну строку через пробел)
        puts("Введите значения массива: ");
        for (int i = 0; i < size_of_array; i++) {
            scanf("%ld", &array[i]);
        }
    } else {
        // Произвольный массив
        size_of_array = 100000;
        long _a[100000];
        array = _a;
        // Генерация произвольного массива
        for (size_t i = 0; i < size_of_array; i++) {
            array[i] = rand() % 10000;
        } 
    }
    // Сортировка массива
    split_and_sort_array(array, size_of_array, NUMBER_OF_THREADS);
    // Вывод отсортированного массива
    puts("Отсортированный массив:");
    for (int i = 0; i < size_of_array; i++) {
        printf("array[%d] = %ld\n", i, array[i]);
    } 
    return 0;
}