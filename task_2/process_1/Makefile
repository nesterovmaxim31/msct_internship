objects = main.o chat.o
flags = -c 

exe_process_1 : $(objects)
	gcc -g -o exe_process_1 $(objects)

main.o : main.c chat.h
	gcc $(flags) main.c 

chat.o : chat.c chat.h 
	gcc $(flags) chat.c

clean :
	rm -f *.o 