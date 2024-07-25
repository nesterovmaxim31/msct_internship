objects = main.o sort_core.o compare_func.o
flags = -c -g

task_3 : $(objects)
	gcc -g -o task_3 $(objects)

main.o : main.c sort_core.h
	gcc $(flags) main.c

sort_core.o : sort_core.c sort_core.h
	gcc $(flags) sort_core.c

compare_func.o : compare_func.c compare_func.h
	gcc $(flags) compare_func.c

.PHONY: clean
clean : 
	rm -f task_3 *.o