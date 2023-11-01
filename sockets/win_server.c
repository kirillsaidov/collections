#include<stdio.h>
#include<winsock2.h>

// #pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[]) {    
    // initialize winsockets
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    // could not create sockset
    SOCKET sock_server = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_server == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    // create connection address
    struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

    return 0;
}