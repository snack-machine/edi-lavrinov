#include "utils.h"


Client* clients[MAX_NUMBER_OF_CLIENTS];
static int client_id = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void insert_client_to_queue(Client* client)
{
	pthread_mutex_lock(&mutex);

    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
    {
        if (!clients[i])
        {
            clients[i] = client;
        }
    }

    pthread_mutex_unlock(&mutex);
}

void remove_client_from_queue(int client_id)
{
	pthread_mutex_lock(&mutex);

    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
    {
        if (clients[i] && clients[i]->id == client_id)
        {
            clients[i] = 0;
            break;
        }
    }

    pthread_mutex_unlock(&mutex); 
}

void send_message_to_all(char* message, int client_id)
{
	pthread_mutex_lock(&mutex);

    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
    {
        if (clients[i] && clients[i]->id != client_id)
        {
            handle_error(write(clients[i]->descriptor, message, strlen(message)),
                         "Writing failed");
            break;
        }
    }

    pthread_mutex_unlock(&mutex); 
}

void* handle_client(void* args)
{
    Client* client = (Client*)args;
    char buffer[BUFFER_SIZE + NAME_LENGTH];
    char message_buffer[BUFFER_SIZE];
    char name_buffer[NAME_LENGTH];

    recv(client->descriptor, name_buffer, NAME_LENGTH, 0);
    strcpy(client->name, name_buffer);
    sprintf(buffer, "%s has joined\n", client->name);
    print_message(buffer);    
    send_message_to_all(buffer, client->id);
    bzero(buffer, BUFFER_SIZE);

    while (true)
    {
        int recieved = handle_error(recv(client->descriptor, message_buffer, BUFFER_SIZE, 0),
                                    "Reading is failed");

		if (strlen(buffer) > 0)
        {
            sprintf(buffer, "%s: %s", client->name, message_buffer);
            print_message(buffer);
			send_message_to_all(buffer, client->id);
            bzero(buffer, BUFFER_SIZE);
        }

        bzero(message_buffer, BUFFER_SIZE);
    }

    close(client->descriptor);
    remove_client_from_queue(client->id);
    free(client);

    pthread_detach(pthread_self());

    return 0;
}

int main()
{
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(DEFAULT_IP);
    server_address.sin_port = htons(DEFAULT_PORT);

    int server_socket = handle_error(socket(AF_INET, SOCK_STREAM, 0), "Socket opening failed");

    int option = 1;
    handle_error(setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR,
                            (char*)&option, sizeof(option)), "Failed setting options");

    handle_error(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)), "Binding failed");
    handle_error(listen(server_socket, 10), "Listening failed");


    print_message("Server started successfully");

    struct sockaddr_in client_address;
    int client_socket;
    pthread_t thread_id;

    while (true)
    {
        socklen_t client_address_length = sizeof(client_address);
        client_socket = handle_error(accept(server_socket, (struct sockaddr*)&client_address, &client_address_length),
                                     "Acception failed");

        Client* client = malloc(sizeof(Client));
        client->address = client_address;
        client->descriptor = client_socket;
        client->id = client_id++;
        insert_client_to_queue(client);

        pthread_create(&thread_id, 0, &handle_client, (void*)client);
    }


    close(server_socket);
    close(client_socket);

    return 0;
}
