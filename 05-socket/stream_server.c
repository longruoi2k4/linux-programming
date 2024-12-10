#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h> // Structure of socket.
#include <netinet/in.h> // Lib contains constant, structure of address IP.
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 10
#define MESSAGE_SIZE 256

void chat(int socket_fd) {
    char sendMessage[MESSAGE_SIZE];
    char recvMessage[MESSAGE_SIZE];

    while (1) {
    
    memset(sendMessage, '0', MESSAGE_SIZE);
    memset(recvMessage, '0', MESSAGE_SIZE);

    // Receive message from client
    read(socket_fd, recvMessage, MESSAGE_SIZE);
    printf ("Message from client: %s\n", recvMessage);

    // Respond to clind
    printf("Enter respond message: ");
    fgets(sendMessage, MESSAGE_SIZE, stdin);

    write(socket_fd, sendMessage, sizeof(sendMessage));

    sleep(1);
    }
    
    close(socket_fd);
}

int main(int argc, char *argv[]) 
{
    struct sockaddr_in server_addr, client_addr;
    int port;
    int server_fd, new_socket_fd;

    if(argc < 2) {
        printf("Please enter port number \n ./server <port_number>\n");
        exit(EXIT_FAILURE);
    } else {
        port = atoi(argv[1]);
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
 
    /*Step 1: Create Socket and IP Address*/
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    /*Step 2: Binding*/
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /*Step 3; Listenning*/
    listen(server_fd, LISTEN_BACKLOG);

    int len = sizeof(client_addr);
    while (1) {
        printf("Server is listenning at port %d ...\n", port);
        new_socket_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len);


        printf("Connected sucessful !\n");
        chat(new_socket_fd);
    }

    close(server_fd);
    return 0;
}
