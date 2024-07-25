#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void copy_to_new_file(const char* source_file, int fork_value);
void output_file_data(int fork_value);