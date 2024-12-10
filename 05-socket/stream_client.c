#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h> // Structure of socket.
#include <netinet/in.h> // Lib contains constant, structure of address IP.
#include <arpa/inet.h>
#include <unistd.h>

#define MESSAGE_SIZE 256
void chat(int socket_fd) {
    char sendMessage[MESSAGE_SIZE];
    char recvMessage[MESSAGE_SIZE];

    while (1) {
    
    memset(sendMessage, '0', MESSAGE_SIZE);
    memset(recvMessage, '0', MESSAGE_SIZE);

    // Send message 
    printf("Enter message: ");
    fgets(sendMessage, MESSAGE_SIZE, stdin);
    write(socket_fd, sendMessage, sizeof(sendMessage));

    // Receive message from client
    read(socket_fd, recvMessage, MESSAGE_SIZE);
    printf ("Message from Server: %s\n", recvMessage);

    sleep(1);
    }
    
    close(socket_fd);
}

int main(int argc, char *argv[]) {
    int port;
    int server_fd;
    struct sockaddr_in server_addr;

    memset(&server_addr, '0', sizeof(server_addr));

    if(argc < 3) {
        printf("Please enter: ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }
     port = atoi(argv[2]);

     /*Step 1: Create socket and server address*/
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr); 

    /*Step 2: Connecting */

    connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    chat(server_fd);
}