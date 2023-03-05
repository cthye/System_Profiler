#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    struct sockaddr_in server_addr;
    int client_sd, status;
    char *message = "TAOTAO!!";
    // AF_INET: local communication, SOCK_STREAM: TCP, 0: IP protocol 
    if ((client_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("convert failed");
        exit(EXIT_FAILURE);
    }
    if ((status = connect(client_sd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    send(client_sd, message, strlen(message), 0);
    close(client_sd);
    exit(EXIT_SUCCESS);
}