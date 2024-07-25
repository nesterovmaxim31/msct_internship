objects = main.o stat_call.o
flags = -c

task_6 : $(objects)
	gcc -o task_6 $(objects)

main.o : main.c stat_call.h
	gcc $(flags) main.c

stat_call.o : stat_call.c stat_call.h
	gcc $(flags) stat_call.c

.PHONY: clean
clean : 
	rm -f task_6 *.o