#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory.h>


#include "../utils/calculation.h"
#include "../utils/constant.h"

const char* dat_file = "stat/net_bandwidth.txt";
const char* SERVER_IP = "127.0.0.1";
int PORT = 8088;
double mhz;


int main(int argc, char *argv[]) {
    //*================================
    //* set up server
    //*================================
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("create socket failed");
        exit(-1);
    }

    //* server side
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("bind failed");
        exit(-1);
    }

    if (listen(sock, 1024) < 0) {
        perror("listen failed");
        exit(-1);
    }
   
    int addr_len = sizeof(sin);
    int conn = accept(sock, (struct sockaddr *)&sin, (socklen_t *)&addr_len);
    if (conn < 0) {
        perror("accept failed");
        exit(-1);
    }

    char buf[4096];
    while(1) {
        int read_bytes = read(conn, buf, 4096);
        if (read_bytes == 0) {
            printf("connection is closed\n");
            exit(0);
        } else if (read_bytes < 0) {
            perror("recv failed");
            exit(-1);
        } else {
            printf("recv: %d\n", read_bytes);
        }
    }
    close(sock);
    return 0;
}