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


#define DEFAULT_PORT 32001
#define DEFAULT_IP "127.0.0.1"
#define BUFFER_SIZE 256
#define NAME_LENGTH 32
#define MAX_NUMBER_OF_CLIENTS 3


typedef struct
{
    int descriptor;
    struct sockaddr_in address;

    int id;
    char name[NAME_LENGTH];
} Client;


int handle_error(int result, char* error_message);

char* get_current_time_string();

void print_message(char* message);

#endif
