#include "utils.h"


int clients[NUMBER_OF_CLIENTS];
int clients_number = 0;

pthread_mutex_t mutex;


// void insert_client_to_queue(Client* client)
// {
// 	pthread_mutex_lock(&mutex);

//     for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
//     {
//         if (!clients[i])
//         {
//             clients[i] = client;
//         }
//     }

//     pthread_mutex_unlock(&mutex);
// }

// void remove_client_from_queue(int client_id)
// {
// 	pthread_mutex_lock(&mutex);

//     for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
//     {
//         if (clients[i] && clients[i]->id == client_id)
//         {
//             clients[i] = 0;
//             break;
//         }
//     }

//     pthread_mutex_unlock(&mutex); 
// }

void send_message_to_all(char* message, int message_length)
{
	pthread_mutex_lock(&mutex);

    for (int i = 0; i < clients_number; ++i)
    {
        write(clients[i], message, message_length);
    }

    // for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
    // {
    //     if (clients[i] && clients[i]->id != client_id)
    //     {
    //         handle_error(write(clients[i]->descriptor, message, strlen(message)),
    //                      "Writing failed");
    //         break;
    //     }
    // }

    pthread_mutex_unlock(&mutex); 
}

void* handle_client(void* args)
{
    // Client* client = (Client*)args;
    int client_socket = *((int*)args);

    char buffer[BUFFER_SIZE + NAME_LENGTH];
    char message[BUFFER_SIZE];
    // char name_buffer[NAME_LENGTH];
    int message_length = 0;

    while ((message_length = read(client_socket, message, sizeof(message))) != 0)
    {
        send_message_to_all(message, message_length);
    }

    // Handle clients disconnection
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < clients_number; ++i)
    {
        if (client_socket == clients[i])
        {
            while (i++ < clients_number - 1)
            {
                clients[i] = clients[i + 1];
            }
            break;
        }
    }

    pthread_mutex_unlock(&mutex); 
    close(client_socket);
    return 0;



    // recv(client->descriptor, name_buffer, NAME_LENGTH, 0);
    // strcpy(client->name, name_buffer);
    // sprintf(buffer, "%s has joined\n", client->name);
    // print_message(buffer);    
    // send_message_to_all(buffer, client->id);
    // bzero(buffer, BUFFER_SIZE);

    // while (true)
    // {
    //     int recieved = handle_error(recv(client->descriptor, message_buffer, BUFFER_SIZE, 0),
    //                                 "Reading is failed");

	// 	if (strlen(buffer) > 0)
    //     {
    //         sprintf(buffer, "%s: %s", client->name, message_buffer);
    //         print_message(buffer);
	// 		send_message_to_all(buffer, client->id);
    //         bzero(buffer, BUFFER_SIZE);
    //     }

    //     bzero(message_buffer, BUFFER_SIZE);
    // }

    // close(client->descriptor);
    // remove_client_from_queue(client->id);
    // free(client);

    // pthread_detach(pthread_self());
}

int main()
{
    pthread_mutex_init(&mutex, NULL);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(DEFAULT_PORT);

    int server_socket = handle_error(socket(PF_INET, SOCK_STREAM, 0), "Socket opening failed");
    int socket_option = 1;
    handle_error(setsockopt(server_socket, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&socket_option, sizeof(socket_option)),
                            "Setting socket option failed");
    
    // int option = 1;
    // handle_error(setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR,
    //                         (char*)&option, sizeof(option)), "Failed setting options");

    handle_error(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)), "Binding failed");
    handle_error(listen(server_socket, 20), "Listening failed");


    print_message("Server started successfully \n");

    struct sockaddr_in client_address;
    int client_socket;
    pthread_t thread_id;
    char connection_message[BUFFER_SIZE];

    while (true)
    {
        socklen_t client_address_length = sizeof(client_address);
        client_socket = handle_error(accept(server_socket, (struct sockaddr*)&client_address, &client_address_length),
                                     "Acception failed");

        pthread_mutex_lock(&mutex);
        clients[clients_number] = client_socket;
        clients_number++;
        pthread_mutex_unlock(&mutex);

        // Client* client = malloc(sizeof(Client));
        // client->address = client_address;
        // client->descriptor = client_socket;
        // client->id = client_id++;
        // insert_client_to_queue(client);

        pthread_create(&thread_id, 0, &handle_client, (void*)&client_socket);
        pthread_detach(thread_id);

        // TODO print smth not IP
        sprintf(connection_message, "Connected user with IP: %s \n", inet_ntoa(client_address.sin_addr));
        print_message(connection_message);

        // sleep(3);
    }

    // close(client_socket);

    close(server_socket);
    pthread_mutex_destroy(&mutex);

    return 0;
}
