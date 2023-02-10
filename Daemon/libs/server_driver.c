#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "../includes/server_driver.h"

void time_service(int* client_fd) {
    time_t t_ime;
    printf("Connected to a client \n");

    client_request req;
    read(*client_fd, &req, sizeof(&t_ime));

    if (req) {
        t_ime = time(NULL);
        send(*client_fd, &t_ime, sizeof(t_ime), 0);
        printf("Time in epoch format is sent. \n");
    } else {
        printf("Garbage request from client-side received! \n");
    }
}


extern void drive() {
    int exi_t = 0;
    int opt = 1;
    struct sockaddr_in servr_sock;
    size_t addr_len = sizeof(servr_sock);

    int s_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (s_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsocketopt");
        exit(EXIT_FAILURE);
    }

    servr_sock.sin_family = AF_INET;
    servr_sock.sin_addr.s_addr= inet_addr("127.0.0.1");
    servr_sock.sin_port = htons(5606);

    if (bind(s_fd, (struct sockaddr*)&servr_sock, sizeof(servr_sock)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s_fd, 128) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(!exi_t) {
        int client_fd;
        printf("listening on port: 5606. \n");

        if ((client_fd = accept(s_fd, (struct sockaddr* )&servr_sock, (socklen_t* )&addr_len)) < 0) {
            perror("accept");
            continue;
        } else {
            pthread_t thrd;

            int thred = pthread_create(&thrd, NULL, (void *)&time_service, (void *)&client_fd);
            if (thred < 0) {
                perror("pthread_create");
            }
        }
    }

    return;
}
