#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>

#define PORT 8080

void PIPEhandler(int sig) {
    signal(sig, SIG_IGN);
    printf("yahooo~\n");
    exit(EXIT_FAILURE);
}

int main() {
    signal(SIGPIPE, PIPEhandler);
    struct sockaddr_in address;
    int server_sd, conn;
    int addrlen = sizeof(address);
    char *message = "T";
    char buffer[56] = {'0'};
    // AF_INET: local communication, SOCK_STREAM: TCP, 0: IP protocol 
    if ((server_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
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
    while (1) {
        if ((conn = accept(server_sd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        if (recv(conn, buffer, sizeof(buffer), 0) < 0) {
            perror("receive failed");
            exit(EXIT_FAILURE);
        }
        if (send(conn, message, strlen(message), 0) < 0) {
            perror("send failed");
            exit(EXIT_FAILURE);
        }
    }
    close(server_sd);
    close(conn);
    exit(EXIT_SUCCESS);
}