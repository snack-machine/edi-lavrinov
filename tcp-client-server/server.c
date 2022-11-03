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

    if (bind(socket_descriptor, (struct sockaddr*)&address, sizeof address) == -1) 
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_descriptor, 5) == -1) 
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    socklen_t address_length = sizeof address;

    int client_descriptor = accept(socket_descriptor, (struct sockaddr*)&address, &address_length);
    if (client_descriptor == -1) 
    {
        perror("Acception failed");
        exit(EXIT_FAILURE);
    }

    size_t read_bytes;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        read_bytes = read(client_descriptor, buffer, BUFFER_SIZE);
        if (read_bytes == -1) 
        {
            perror("Reading failed");
            exit(EXIT_FAILURE);
        }

        write(STDOUT_FILENO, buffer, read_bytes);
        write(client_descriptor, buffer, read_bytes);

        sleep(3);
    }

    close(client_descriptor);
    close(socket_descriptor);

    return 0;
}
