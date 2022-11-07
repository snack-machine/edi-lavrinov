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

char* get_current_time_string()
{
    char result[128];
    time_t raw_time;
    struct tm* time_object;

    time(&raw_time);
    time_object = localtime(&raw_time);

    sprintf(result, "[%d:%d:%d]", time_object->tm_hour, time_object->tm_min, time_object->tm_sec);
    
    return result;
}

void print_message(char* message)
{
    printf("%s %s", get_current_time_string(), message);
    // fflush(stdout);
}
