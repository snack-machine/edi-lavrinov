#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define DEFAULT_PORT 4444
#define DEFAULT_IP "127.0.0.1"
#define BUFFER_SIZE 256
#define NAME_LENGTH 32
#define NUMBER_OF_CLIENTS 16


int handle_error(int result, char* error_message);

void get_current_time_string(char* time_string);

void print_message(char* message);

#endif
