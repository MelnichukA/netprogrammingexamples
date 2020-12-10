#include "single_thread_tcp_server.h"

unsigned int HashFAQ6(const char * str);

void handle_connection(SOCKET socket, sockaddr_in* addr) {
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");

    while (true) {
        char buffer[256] = "";
        int rc = recv(socket, (char *) &buffer, sizeof(buffer), 0);
        if (rc > 0) {
            printf("Received: %s\n", buffer);
            printf("Hash: %u\n", HashFAQ6(buffer));
        }
        else {
            break;
        }
    }
    close_socket(socket);

    printf("[%s]>>%s", str_in_addr, "Close incomming connection\n");
}

unsigned int HashFAQ6(const char * str)
{

    unsigned int hash = 0;

    for (; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}