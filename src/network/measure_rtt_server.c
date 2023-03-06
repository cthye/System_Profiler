#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    struct sockaddr_in address;
    int server_sd, conn;
    int addrlen = sizeof(address);
    char *message = "TAOTAO!!TAOTAO!!TAOTAO!!TAOTAO!!TAOTAO!!TAOTAO!!TAOTAO!!TAOTAO!";
    char buffer[1024] = {'0'};
    // AF_INET: local communication, SOCK_STREAM: TCP, 0: IP protocol 
    if ((server_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_sd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_sd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    if ((conn = accept(server_sd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    while (1) {
        read(conn, buffer, 1024);
        send(conn, message, strlen(message), 0);
    }
    close(server_sd);
    exit(EXIT_SUCCESS);
}