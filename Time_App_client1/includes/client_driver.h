#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#ifndef CLIENT_DRIVER_H
#define CLIENT_DRIVER_H

//for sending requests
typedef enum request{
    ssend=1
} client_request;

// enumation class for choice that will be compared to the user input in the switch function
typedef enum choice {

    conn = 1,
    req,
    disconn,
    quit

} chce;

// structure which checks for the connection establishment
typedef struct client_info
{
    int status;

} client_status;

extern void drive();

#endif 
