#include "finding_algorithm.h"

// Выводит наденный максимальный отрезок
void print_answer(long *array, size_t size_of_array, size_t left_index) {
    printf("Найденная подпоследовательность: ");
    for (size_t i = left_index; i < (left_index + size_of_array); i++) {
        printf("%ld ", array[i]);
    }
    puts("");
}

// Сначала по алгоритму Кадана найту все непрерывные последовательности с максимальной длиной
void find_max_sum(long *array, size_t size_of_array) {
    // max_sum - максимальная сумма (ответ), current_sum - текущая частиная сумма, 
    // minus_pos - индекс, накотором заканчивает отрицательная(не интересующая нас) подпоследовательность
    long max_sum = array[0], current_sum = 0, minus_pos = -1;
    // left_index, right_index - левый и правый индекс соотвественно самого большого непрерывного кусочка с макс. суммой
    // max_leght - максимальная найденная длина
    size_t  left_index = 0, right_index = 0, max_leght = 0;
    for (size_t i = 0; i < size_of_array; i++) {
        current_sum += array[i];
        if (current_sum > max_sum) {
            max_sum = current_sum;
            left_index = minus_pos + 1;
            right_index = i;
            max_leght = right_index - left_index + 1;
        }
        // Если суммы равны, выбираем подподследовательность с большей длиной
        else if (current_sum == max_sum) {
            // Если длина рассматриваемой, больше чем длина уже найденной, переписываем
            if (i - minus_pos >= max_leght) {
                left_index = minus_pos + 1;
                right_index = i;
                max_leght = right_index - left_index + 1;
            } 
        }
        // Если текущая набранная сумма отрицательна, она точно не может быть частью с максимальной суммой
        // Поэтому обнуляем её и ставим минус-индекс на i (текущий)
        if (current_sum < 0) {
            current_sum = 0;
            minus_pos = i;
        }
    }
    // Вывод результатов поиска
    printf("Максимальная найденная сумма подпоследовательности равна: %ld и её длина: %lu\n", max_sum, max_leght);
    // Вывод найденной подпоследовательности
    print_answer(array, max_leght, left_index);
}