objects = main.o chat.o math_operation.o
flags = -c 

exe_process_2 : $(objects)
	gcc -g -lm -o exe_process_2 $(objects)

main.o : main.c chat.h
	gcc $(flags) main.c 

chat.o : chat.c chat.h math_operation.h
	gcc $(flags) chat.c

math_operation.o : math_operation.c math_operation.h
	gcc $(flags) -lm math_operation.c

clean :
	rm -f *.o 