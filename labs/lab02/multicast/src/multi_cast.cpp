#include "multi_cast.h"
#include <ctime>

void parse_cmd_line(int argc, char **argv, PMULTICAST_GROUP_OPTION opts) {
	int i;
    strcpy(opts->ip_interface, "");
    strcpy(opts->group_ip_interface, MCASTADDR);
	opts->group_port = MCASTPORT;
    opts->is_sender = false;
    opts->is_receiver = false;
    opts->is_loop_back = false;
    opts->repeat_count = DEFAULT_COUNT;
    opts->receive_timeout = 10000;

	for (i = 1; i < argc; i++) {
		if ((argv[i][0] == '-') || (argv[i][0] == '/')) {
			switch (tolower(argv[i][1])) {
			    case 's': //
			    case 'r': //
			        opts->is_sender = tolower(argv[i][1]) == 's';
				    opts->is_receiver = tolower(argv[i][1]) == 'r';
				    break;
			    case 'm': //
				    if (strlen(argv[i]) > 3) {
				        strcpy(opts->group_ip_interface, &argv[i][3]);
				    }
				    break;
			    case 'i': //
				    if (strlen(argv[i]) > 3) {
                        strcpy(opts->ip_interface, &argv[i][3]);
                    }
				    break;
			    case 'p': //
				    if (strlen(argv[i]) > 3) {
				        opts->group_port = atoi(&argv[i][3]);
				    }
				    break;
			    case 'l': //
				    opts->is_loop_back = true;
				    break;
			    case 'n': //
				    opts->repeat_count = atoi(&argv[i][3]);
				    break;
                case 't': //
                    opts->receive_timeout = atoi(&argv[i][3]);
                    break;
			}
		}
	}
}

int group_sender(PMULTICAST_GROUP_OPTION opts, SOCKET socket, struct sockaddr_in* to) {
    unsigned int i = 0;
    socklen_t ret,ter;

    for (i = 0; i < opts->repeat_count; ++i)
    {
        char sendbuf[BUFSIZE];
        printf("Try to send...\n");
        sprintf(sendbuf, "server 1: This is a test: %ld", i);
        ret = sendto(socket, (char*)sendbuf, strlen(sendbuf), 0, (struct sockaddr*)to, sizeof(sockaddr_in));
        CHECK_IO(ret, -1, "Error send data in group\n");
        current_thread_sleep(500);

		char msg[256] = "";
		printf("%s", "Enter msg:");
		scanf("%[^\n]s", msg);
		ret = sendto(socket, msg, sizeof(msg), 0, (sockaddr*)&to, sizeof(sockaddr_in));
		CHECK_IO(ret, -1, "Error send data in group\n");

		int leng = sizeof(to);
		char time_str[256];
		ter = recvfrom(socket, time_str, sizeof(time_str), 0, (struct sockaddr*)&to, &leng);
		CHECK_IO(ter, -1, "Error send data in group\n");
		current_thread_sleep(500);
    }
    return 0;
}

int group_receiver(PMULTICAST_GROUP_OPTION opts, SOCKET socket) {
	sockaddr_in incom_addr;
	memset(&incom_addr, 0, sizeof(incom_addr));
	socklen_t len = sizeof(incom_addr);
	char buffer[256] = "";
	int rec_cn = recvfrom(socket, buffer, sizeof(buffer), 0, (sockaddr*)&incom_addr, &len);

	if (rec_cn <= 0) {
		error_msg("Can't receive data");
	}

	printf("[From: %s] Received data [%s]\n", inet_ntoa(incom_addr.sin_addr), buffer);


	time_t t1;
	time(&t1);
	char buff[256];
	char* time_str = ctime(&t1);
	strcpy(buff, time_str);
	int buff_len = sizeof(buff);
	rec_cn = sendto(socket, buff, buff_len, 0, (sockaddr*)&incom_addr, len);
	if (rec_cn <= 0) {
		error_msg("Can't send data");
	}
    return 0;
}
