#include "simple_tcp_client.h"

void exit_handler();

SOCKET client_socket;
int main(int argc, char* argv[])
{
    atexit(common_exit_handler);
    atexit(exit_handler);
	short port;
	char host[128] = "";
	bool parse_cmd_result = parse_cmd(argc, argv, host, &port);

	if (!parse_cmd_result )//|| !host || !strlen(host))
	{
		printf("Invalid host or port. Usage %s -h host -p port\n", argv[0]);
		return -1;
	}

    common_init_handler ();

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket <= 0) {
		error_msg("Can't create socket");
		return -1;
	}

	struct sockaddr_in server_addr{};
	init_inet_address(&server_addr, host, port);

	//Connect to the server
	if (connect(client_socket, (sockaddr*)&server_addr, sizeof(sockaddr))) {
		char err_msg[128] = "";
		sprintf(err_msg, "Can't connect to the server %s:%d", host, port);
		error_msg(err_msg);
		return -1;
	}

	printf("Connection to the server %s:%d success\n", host, port);

    char buffer[20] = "";
    char path[100] = "files/Test.txt";

    FILE *fd = fopen(path, "r");
    int bytes_read;

    while (!feof(fd)) {
        if ((bytes_read = fread(&buffer, sizeof(char), 20, fd)) > 0)
            send(client_socket, buffer, bytes_read, 0);
        else
            break;
    }

    fclose(fd);
    printf("Text: %s\n", buffer);

	close_socket(client_socket);

	return 0;
}

void exit_handler()
{
	close_socket(client_socket);
}
