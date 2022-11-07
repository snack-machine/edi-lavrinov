#include "utils.h"


int handle_error(int result, char* error_message)
{
    if (result < 0)
    {
        perror(error_message);
        exit(EXIT_FAILURE);
    }
    
    return result;
}

void get_current_time_string(char* time_string)
{
    time_t raw_time;
    struct tm* time_object;

    time(&raw_time);
    time_object = localtime(&raw_time);

    sprintf(time_string, "[%d:%d:%d]", time_object->tm_hour, time_object->tm_min, time_object->tm_sec);
}

void print_message(char* message)
{
    char* timestamp = malloc(sizeof(char) * 128);
    get_current_time_string(timestamp);
    printf("%s %s", timestamp, message);
    // fflush(stdout);
    free(timestamp);
}
