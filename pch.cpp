// pch.cpp: source file corresponding to the pre-compiled header
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "pch.h"
#include <time.h>

void waitForSecs(unsigned int secs) {
	unsigned int retTime = time(0) + secs;
	while (time(0) < retTime);
}
void telnet_send_command(SOCKET sock, const char* command) {
    send(sock, command, strlen(command), 0);
    send(sock, "\r\n", 2, 0);
    waitForSecs(1);
}

int telnet_receive_response(SOCKET sock, bool display, char* destbuffer) {
    char buffer[4096];
    int bytes_received;

    bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    waitForSecs(1);
    if (bytes_received == SOCKET_ERROR) {
        printf("Error receiving data from the server\n");
        return 0;
    }

    buffer[bytes_received] = '\0';
    if (display) {
        strcpy(destbuffer, buffer);
    }
}
int validate(char* machine, char* result) {
    if (strcmp("reboot", result)) {
        printf("HIM %s success\n", machine);
        return 1;
    }
    else {
        printf("HIM %s return ERROR\n", machine);
        return 0;
    }
    return 0;
}
