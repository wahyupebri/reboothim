// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>
// add headers that you want to pre-compile here
void waitForSecs(unsigned int secs);
void telnet_send_command(SOCKET sock, const char* command);
int telnet_receive_response(SOCKET sock, bool display, char* destbuffer);
int validate(char* machine, char* result);
#endif //PCH_H