objects = main.o finding_algorithm.o 
flags = -c

task_9 : $(objects)
	gcc -o task_9 $(objects)

main.o : main.c finding_algorithm.h
	gcc $(flags) main.c

finding_algorithm.o : finding_algorithm.c finding_algorithm.h
	gcc $(flags) finding_algorithm.c


.PHONY : clean
clean : 
	rm -f task_9 *.o 
