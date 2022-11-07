#include "utils.h"


int client_socket;
char name_buffer[NAME_LENGTH];


void send_message_handler()
{
    char message_buffer[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    while (true)
    {
        fgets(message_buffer, BUFFER_SIZE, stdin);
        sprintf(buffer, "%s: %s\n", name_buffer, message_buffer);
        send(client_socket, buffer, strlen(buffer), 0);

        bzero(message_buffer, BUFFER_SIZE);
        bzero(buffer, BUFFER_SIZE);
    }
}

void receive_message_handler()
{
    char message_buffer[BUFFER_SIZE];

    while (true)
    {
        handle_error(recv(client_socket, message_buffer, BUFFER_SIZE, 0),
                     "Receiving failed");
        print_message(message_buffer);

        bzero(message_buffer, BUFFER_SIZE);
    }
}

int main()
{
    print_message("Enter your name: ");
    fgets(name_buffer, NAME_LENGTH, stdin);
    
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(DEFAULT_IP);
    client_address.sin_port = htons(DEFAULT_PORT);

    client_socket = handle_error(socket(AF_INET, SOCK_STREAM, 0), "Socket opening failed");

    handle_error(connect(client_socket, (struct sockaddr*)&client_address, sizeof(client_address)),
                 "Connection failed");

    send(client_socket, name_buffer, NAME_LENGTH, 0);

    
    print_message("You've successfully connected.");

    pthread_t send_message_thread;
    pthread_create(&send_message_thread, 0, (void*)send_message_handler, 0);

    pthread_t receive_message_thread;
    pthread_create(&send_message_thread, 0, (void*)receive_message_handler, 0);
    

    close(client_socket);

    return 0;
}
