objects = main.o parse_core.o counting_core.o
flags = -c -g 

task_10 : $(objects)
	gcc -lm -g -o task_10 $(objects)

main.o : main.c parse_core.h
	gcc $(flags) main.c

parse_core.o : parse_core.c parse_core.h
	gcc $(flags) parse_core.c

counting_core.o : counting_core.c counting_core.h parse_core.h
	gcc $(flags) counting_core.c

.PHONY : clean
clean : 
	rm -f task_10 *.o 
