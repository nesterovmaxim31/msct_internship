objects = main.o merge_sort.o secondary_functions.o pthread_core.o
flags = -pthread -c

task_1 : $(objects)
	gcc -pthread -o task_1 $(objects)

main.o : main.c pthread_core.h
	gcc $(flags) main.c

merge_sort.o : merge_sort.c merge_sort.h
	gcc $(flags) merge_sort.c

secondary_functions.o : secondary_functions.c secondary_functions.h
	gcc $(flags) secondary_functions.c

pthread_core.o : pthread_core.c pthread_core.h secondary_functions.h merge_sort.h
	gcc $(flags) pthread_core.c

.PHONY : clean
clean:
	rm -f *.o task_1
