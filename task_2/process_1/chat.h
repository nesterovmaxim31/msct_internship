#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TRUE 1


void start_chat(const char* path_to_named_pipe_in, const char* path_to_named_pipe_out);
void send_request(int file_descriptor, char* message, size_t message_lenght);
void answer_request(int file_descriptor, char* message, size_t message_lenght);