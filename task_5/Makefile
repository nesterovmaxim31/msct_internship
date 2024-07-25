objects = main.o rmdir_call.o
flags = -c

task_5 : $(objects)
	gcc -o task_5 $(objects)

main.o : main.c rmdir_call.h
	gcc $(flags) main.c

rmdir_call.o : rmdir_call.c rmdir_call.h
	gcc $(flags) rmdir_call.c

.PHONY: clean
clean : 
	rm -f task_5 *.o