#include "pthread_core.h"

// В данном файле будет реализована многопоточность
// Функция, которая даётся в качестве аргумента каждому потоку. Отвечает за сортировку и объединение процессов
void* sort_array_p(void* arg) {
    // Размер рассматриваемого кусочка (степени двойки)
    size_t size_of_current_piece = 1;
    data_t* thread_data = (data_t*) arg;
    // Изменяет статус в работе
    thread_data -> current_status = at_work;
    sort_array(&(thread_data -> array)[thread_data -> left_index], &(thread_data -> supporting_array)[thread_data -> left_index],(thread_data -> right_index) - (thread_data -> left_index));
    // Пока увеличение рассматриваемых кусочков не превысит их количество
    for (size_t j = 0; j <= (func_log2(thread_data -> amout_of_pieces) + 1); j++) {
        // Размеры кусочков увеличиваются квадратично
        size_of_current_piece *= 2;
        // С увелечением кусочка, один процесс поглощает другой. 
        // С помощью оператора остатка от деления % вычисляем какие процессы завершать, а какие увеличивать
        if ((thread_data -> index) % size_of_current_piece != 1 || thread_data -> index == thread_data -> amout_of_pieces) {
            thread_data -> current_status = finished;
            return NULL;
        } else {
            size_t right_index_thread = min_pair(thread_data -> amout_of_pieces, thread_data -> index + size_of_current_piece / 2);
            // Ожидание, когда закончится поглощаемый процесс
            while ((thread_data -> pointer_to_arg)[right_index_thread - 1].current_status < finished) {}
            // Создаём границы увеличнного кусочка. Из поглощаемого процесса получаем его границы
            size_t new_piece_right_index_array = (thread_data -> pointer_to_arg)[right_index_thread - 1].right_index;
            size_t new_piece_left_index_array = (thread_data -> pointer_to_arg)[right_index_thread - 1].left_index;
            // Присваиваем правую границу поглощаемого процесса данному
            thread_data -> right_index = new_piece_right_index_array;
            // Отправляем данной функции два отсортированных кусочка для объединения
            comparator(thread_data -> array, thread_data -> supporting_array, new_piece_right_index_array,
            thread_data -> left_index, new_piece_left_index_array);
            // Копируем данные из вспомогательного массива в основной согласно алгоритму сортировки слиянием
            memcpy(thread_data -> array, thread_data -> supporting_array, thread_data -> size_of_array * sizeof(long));
        }
    }
    return NULL;
}

// Весь массив разибивается на равные кусочи (в зависимости от количества потоков и длины массива последний кусок может быть меньше)
void split_and_sort_array(long* array, size_t size_of_array, size_t number_of_threads) {
    // Случай, при котором массив состоит из одного значения
    if (size_of_array == 1) return;
    // Создание вспомагательного массива
    long* supporting_array;
    supporting_array = (long*)malloc(sizeof(long) * size_of_array);
    memcpy(supporting_array, array, size_of_array * sizeof(long));
    // Размер массива, предназначатый потоку в начале для сортировки
    size_t size_whole_pieces = size_of_array / number_of_threads;
    // Размер остаточного кусочка (может быть равен нулю, если количество элементов массива делится без остатка на количество потоков)
    // Этот кусочек будет добавлен к самому последнему целому
    size_t size_residual_piece = size_of_array % number_of_threads;
    // Случай, когда количество потоков больше, чем половина от количество элементов массива
    if (size_whole_pieces < 2) {
        size_whole_pieces = 2;
        size_residual_piece = size_of_array % 2;
    }
    // Общее количество кусочков
    size_t amout_of_pieces = size_of_array / size_whole_pieces;
    // Указатель на массив pthread_t
    pthread_t* threads_id_array;
    threads_id_array = (pthread_t*)malloc(sizeof(pthread_t) * amout_of_pieces);
    // Указатель на массив структур данных для каждого потока
    data_t* arg_for_thread;
    arg_for_thread = (data_t*)malloc(sizeof(data_t) * (size_whole_pieces + amout_of_pieces));
    // Перебираем все кусочки, давая каждого из них некоторому потоку
    for (size_t i = 0; i < amout_of_pieces; i++) {
        // У каждого потока есть своя структура данных
        arg_for_thread[i].array = array;
        arg_for_thread[i].supporting_array = supporting_array;
        arg_for_thread[i].size_of_array = size_of_array;
        arg_for_thread[i].index = i + 1;
        arg_for_thread[i].current_status = not_init;
        arg_for_thread[i].pointer_to_arg = arg_for_thread;
        arg_for_thread[i].left_index = i * size_whole_pieces;
        arg_for_thread[i].amout_of_pieces = amout_of_pieces;
        // Случай, когда размер последнего кусочка отличается
        if (i == (amout_of_pieces - 1)) {
            arg_for_thread[i].right_index = arg_for_thread[i].left_index + size_whole_pieces + size_residual_piece;
        } 
        // Случай, когда размер последнего кусочка равен другим
        else {
            arg_for_thread[i].right_index = arg_for_thread[i].left_index + size_whole_pieces;
        }
        // Запускаем многопоточность, дав каждому потоку свой кусочек 
        pthread_create(&threads_id_array[i], NULL, sort_array_p, &arg_for_thread[i]);
    }
    // Ожидается завершение первого потока, так как он в итоге объеденяет в себе все другие
    pthread_join(threads_id_array[0], NULL);
}