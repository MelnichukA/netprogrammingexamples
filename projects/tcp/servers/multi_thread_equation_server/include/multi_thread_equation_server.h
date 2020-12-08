#ifndef NETWORK_PROGRAMMING_MULTI_THREAD_SERVER_H
#define NETWORK_PROGRAMMING_MULTI_THREAD_SERVER_H

#include "common_net.h"
#include "common_thread.h"
#include "shared_tcp_structs.h"
#include "math.h"

#include <vector>

#define DEFAULT_PORT 5557
#define CONNECTION_QUEUE 100

SquareRootResponse* compute(SquareRootRequest*, SquareRootResponse*);

THREAD_VOID handle_connection(void*);
#endif //NETWORK_PROGRAMMING_MULTI_THREAD_SERVER_H
