#include "common.h"


int main()
{
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) 
    {
        perror("Socket opening failed");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(DEFAULT_PORT);

    if (inet_pton(AF_INET, DEFAULT_IP, &address.sin_addr) == -1) 
    {
        perror("Failed inet_pton");
        exit(EXIT_FAILURE);
    }

    if (connect(socket_descriptor, (struct sockaddr*)&address, sizeof address) == -1) 
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t read_bytes;
    size_t counter = 0;
    char data_to_send[] = "Data # \n";

    while (1)
    {
        data_to_send[6] = counter + '0';
        counter++;

        write(socket_descriptor, data_to_send, sizeof data_to_send);
        read_bytes = read(socket_descriptor, buffer, BUFFER_SIZE);

        if (read_bytes == -1) 
        {
            perror("read failed");
            exit(EXIT_FAILURE);
        }

        write(STDOUT_FILENO, buffer, read_bytes);
        sleep(3);
    }

    close(socket_descriptor);

    return 0;
}
