#include "udp_time_receiver.h"
#include <ctime>
#include <cstring>


bool process_receiv_data(SOCKET socket) {
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
	

	return true;
}
