#ifndef NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H
#define NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H

#include "common_net.h"

#define DEFAULT_PORT 5557
#define CONNECTION_QUEUE 100

void handle_connection(SOCKET, sockaddr_in*);

struct LaunchProgRequest {
    char data[256];
};

struct LaunchProgResponse {
    char data[256];
};

#endif //NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H
