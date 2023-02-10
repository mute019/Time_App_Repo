#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "../includes/client_driver.h"
#define MAX_CHAR 30

//IP address verification & configuration
int is_validate_ip(struct sockaddr_in* sock, const char* ip) {
    if (inet_pton(AF_INET, ip, &(sock->sin_addr))) {
        return 1;
    } else {
        return 0;
    }
}

//function for establishing the connection to the server.
void establish_conn(client_status **client_stat, struct sockaddr_in* servr) {
    //servr->sin_addr.s_addr = inet_addr("127.0.0.1");
    servr->sin_family = AF_INET;
    servr->sin_port = htons(5606);

    *client_stat = (client_status* )malloc(sizeof(client_status));
    if (!(*client_stat)) {
        printf("Something went wrong! \nCould not establish connection to the Host.!\n");
        return;
    }

    if (((*client_stat)->status = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }

    int ret = connect((*client_stat)->status, (struct sockaddr* )servr, sizeof(*servr));
    if (ret < 0) {
        close((*client_stat)->status);
        free(*client_stat);
        *client_stat = NULL;
        perror("connect");
    }

    return;
}


//Here I am checking for both the connection of the client and server. 
//Hence, depending on the situation connecting to the server

void connectivity(client_status **client_stat, struct sockaddr_in* servr) {
    if (is_validate_ip((struct sockaddr_in* )&servr, "127.0.0.1")) {

            if (*client_stat) {
                printf("Connection is already established!!\n");
            } else {
                establish_conn(&(*client_stat), (struct sockaddr_in*)&servr);
                if (*client_stat && ((*client_stat)->status != -1)) {
                    printf("Connection has been successfully established!\n");
                } else {
                    printf("Connection could not be established!\n");
                }
            }

        } else {

            printf("Something Went Wrong!!\n");
        }
}


//This is the function contacting the server for the epoch time 
//which then exposes the API for fetching the time
int64_t getTime(client_status** client_stat) {
    if (!(*client_stat)) {
        printf("Not connected to any client! \n");
        return 0;
    }

    time_t read_time;
    //sending request to the server
    client_request requ = ssend;
    int snd_msg = send((*client_stat)->status, &requ, sizeof(read_time), 0);
    if (snd_msg == -1) {
        printf("Time request could not be sent, try again!\n");
        close((*client_stat)->status);
        free(*client_stat);
        *client_stat = NULL;
        return 0;    
    }

    int rd_ = read((*client_stat)->status, &read_time, sizeof(read_time));

    if (rd_ == -1) {
        printf("Time could not be read, try again!");
        close((*client_stat)->status);
        free(*client_stat);
        *client_stat = NULL;
        return 0; 
    }

    //printf("The Time in Epoch format is : %ld \n", read_time);
    return read_time;
}

//this the driver code which invokes above function on appropriate input
extern void drive() {
    //printf("Client is running is Connecting..");
    //char* str = "Hello World";

    client_status* client_stat = NULL;
    struct sockaddr_in servr;

    int exit = 0;

    while(!exit) {
        //fflush(stdout);
        printf("\nTime Fetcher \n\n");
        printf("\n1. Connect to the Server.");
        printf("\n2. Fetch Current Time from the server.");
        printf("\n3. Disconnect the server.");
        printf("\n4. Quit. \n");
        printf("\nEnter Your Choice : ");

        int ch;
        scanf("%d", &ch);
        fflush(stdin);

        switch (ch) {

            case conn: {
                client_stat = NULL;
                connectivity(&client_stat, &servr);
                break;
            }

            case req: {
                int64_t epoch_time = getTime(&client_stat);
                if (!epoch_time) {
                    //printf("Time could not be fetched!");
                    break;
                }
                printf("The Time in Epoch format is : %ld \n", epoch_time);
                break;
            }

            case disconn: {
                if (!client_stat) {
                    printf("Not connected to the host. \n");
                    break;
                }

                close(client_stat->status);
                free(client_stat);
                client_stat = NULL;
                printf("Disconnected!\n");
                break;
            }

            case quit: {
                if (client_stat) {
                    close(client_stat->status);
                    free(client_stat);
                    client_stat = NULL;
                }
                exit = 1;
                break;
            }

            default:
                printf("Wrong Choice! \n");
                break;
            }
    }
}
