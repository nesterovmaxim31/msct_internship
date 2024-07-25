objects = main.o parse_line.o
flags = -c -g

prg : $(objects)
	gcc -g -o prg $(objects)

main.o : main.c parse_line.h
	gcc $(flags) main.c

parse_line.o : parse_line.c parse_line.h
	gcc $(flags) parse_line.c

.PHONY: clean
clean : 
	rm -f prg *.o