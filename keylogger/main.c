#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        perror("error: empty filename\n");
        return -1;
    }

    char* cP_logfile_path = argv[1];


    FILE* objP_output_file = fopen(cP_logfile_path, "w");

    if (NULL == objP_output_file)
    {
        perror("error: can't open the file\n");
        return -1;        
    }


    char cL_buffer[128];
    time_t s32L_rawtime;
    struct tm* objP_time;

    for (char byte; read(STDIN_FILENO, &byte, 1) > 0; )
    {
        time(&s32L_rawtime);
        objP_time = localtime(&s32L_rawtime);
        
        sprintf(cL_buffer, "[%d.%d.%d %d:%d:%d] %c\n", 
                objP_time->tm_mday, objP_time->tm_mon + 1, objP_time->tm_year + 1900,
                objP_time->tm_hour, objP_time->tm_min, objP_time->tm_sec, byte);

        fputs(cL_buffer, objP_output_file);
        fflush(objP_output_file);
    }

    fclose(objP_output_file);

    return 0;
}
