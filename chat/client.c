#include "utils.h"


int client_socket;
char name[NAME_LENGTH];


void* send_message_handler(void* args)
{
    int socket = *((int*)args);
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    char name_and_message[NAME_LENGTH + BUFFER_SIZE + 1];

    print_message("[Action] You've successfully connected \n");
    sprintf(buffer, "[Action] %s has joined \n", name);
    write(socket, buffer, strlen(buffer));

    while (true)
    {
        fgets(message, BUFFER_SIZE, stdin);

        if (!strcmp(message, "quit\n"))
        {
            sprintf(name_and_message, "[Action] %s has left \n", name);
            write(socket, name_and_message, strlen(name_and_message));
            close(socket);
            exit(0);
        }

        sprintf(name_and_message, "%s: %s", name, message);
        write(socket, name_and_message, strlen(name_and_message));
    }

    return 0;
}

void* receive_message_handler(void* args)
{
    int socket = *((int*)args);
    char name_and_message[BUFFER_SIZE + NAME_LENGTH];
    int message_length;

    while (true)
    {
        message_length = read(socket, name_and_message, BUFFER_SIZE + NAME_LENGTH - 1);

        if (message_length > 0)
        {
            name_and_message[message_length] = 0;
            print_message(name_and_message);
        }
    }
}

int main(int argc, char *argv[])
{
    sprintf(name, "%s", argv[1]);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(DEFAULT_IP);
    address.sin_port = htons(DEFAULT_PORT);

    client_socket = handle_error(socket(PF_INET, SOCK_STREAM, 0), "Socket opening failed");

    handle_error(connect(client_socket, (struct sockaddr*)&address, sizeof(address)),
                 "Connection failed");
  
    pthread_t send_message_thread;
    pthread_t receive_message_thread;
    void* thread_return_value;

    pthread_create(&send_message_thread, 0, (void*)send_message_handler, (void*)&client_socket);
    pthread_create(&send_message_thread, 0, (void*)receive_message_handler, (void*)&client_socket);

    pthread_join(send_message_thread, &thread_return_value);
    pthread_join(receive_message_thread, &thread_return_value);

    close(client_socket);

    return 0;
}
