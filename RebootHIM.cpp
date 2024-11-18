#include "pch.h"

#pragma comment(lib, "ws2_32.lib")
// Server details
char server_ip[16] = "";
char server_label[10] = "";
const char* PORT = "23";
const char* USERPASSWORD = "admin";
const char* COMMAND = "triggerReboot\n";

int main(int argc, char* argv[]) {
    // Check if there are enough command-line arguments
    if (argc < 2) {
        printf("Dibuat oleh Wahyu Pebrian, November 2023. Hanya untuk digunakan di site TUTUPAN\n");
        printf("Usage: %s <IP HIM> <Label>\n", argv[0]);
        return 1;
    }

    // Access the input parameter
    char* inputParameter1 = argv[1];
    strcpy(server_ip, inputParameter1);
    char* inputParameter2 = argv[2];
    strcpy(server_label, inputParameter2);
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Error creating socket\n");
        WSACleanup();
        return 1;
    }



    // Convert IP address to binary format
    struct sockaddr_in server_address;
    inet_pton(AF_INET, server_ip, &server_address.sin_addr.s_addr);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(PORT));

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("Error connecting to %s\n", server_label);
        closesocket(sock);
        WSACleanup();
        return 1;
    }
   // Sleep(1);
    telnet_receive_response(sock,false, nullptr);

    // Send username and password
    telnet_send_command(sock, USERPASSWORD);
    telnet_send_command(sock, USERPASSWORD);
    telnet_receive_response(sock, false, nullptr);
    // Send the "TriggerReboot" command
    telnet_send_command(sock, COMMAND);
    Sleep(1);
    char buffer[100]="";

    telnet_receive_response(sock, true, buffer);

    Sleep(1);
    if (validate(server_label, buffer) > 0) {

        closesocket(sock);

        WSACleanup();
        return 0;
    }

    closesocket(sock);

    WSACleanup();
    
    return 1;
}

