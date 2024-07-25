objects = main.o matrix.o signal_handler.o
flags = -c

task_8 : $(objects)
	gcc -o task_8 $(objects)

main.o : main.c matrix.h
	gcc $(flags) main.c

matrix.o : matrix.c matrix.h signal_handler.h
	gcc $(flags) matrix.c

signal_handler.o : signal_handler.c signal_handler.h
	gcc $(flags) signal_handler.c
	
.PHONY: clean
clean : 
	rm -f task_8 *.o 