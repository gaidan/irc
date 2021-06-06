#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080
#define clear() printf("\033[H\033[J")

void *getData(char *ip) {
	while(1) {
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in serv_addr;
		char *msg = "GETDATA";
		char buffer[1024] = {0};
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
		inet_pton(AF_INET, ip, &serv_addr.sin_addr);
		connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		send(sock, msg, strlen(msg), 0);
		read(sock, buffer, 1024);
		close(sock);
		clear();
		printf("%s\n", buffer);
	}
}

void sendMessage(char *handle, char *msg, char *ip) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, ip, &serv_addr.sin_addr);
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	char *nmsg = (char*)malloc(224*sizeof(char));
	sprintf(nmsg, "%s: %s", handle, msg);
	send(sock, nmsg, strlen(nmsg), 0);
	close(sock);
}

int main() {
	char handle[20];
	char iptoconnect[20];
	printf("Handle > ");
	fgets(handle, 20, stdin);
	handle[strcspn(handle, "\n")] = 0;
	sleep(1);
	printf("Server > ");
	fgets(iptoconnect, 20, stdin);
	pthread_t thread;
	pthread_create(&thread, NULL, getData, iptoconnect);
	while (1) {
		char msg[200];
		fgets(msg, 200, stdin);
		msg[strcspn(msg, "\n")] = 0;
		sendMessage(handle, msg, iptoconnect);
	}
}
