sub_dirs = process_1 process_2

start :
	make subsystem
	cd process_2 && mv ./exe_process_2 ../
	cd process_1 && mv ./exe_process_1 ../


subsystem:
	cd process_1 && $(MAKE)
	cd process_2 && $(MAKE)


.PHONY : clean
clean :
	rm -f exe_process_1 exe_process_2
	cd process_1 && $(MAKE) clean
	cd process_2 && $(MAKE) clean 