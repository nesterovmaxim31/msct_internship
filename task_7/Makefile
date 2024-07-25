objects = main.o process_control.o
flags = -c 

task_7 : $(objects)
	gcc -o task_7 $(objects)

main.o : main.c process_control.h
	gcc $(flags) main.c

process_control.o : process_control.c process_control.h
	gcc $(flags) process_control.c

.PHONY: clean
clean : 
	rm -f task_7 *.o parent_copy.txt child_copy.txt