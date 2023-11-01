#ifdef _WIN32
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501  /* Windows XP. */
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    #define CROSSP_SOCKET_INVALID INVALID_SOCKET
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
    #include <unistd.h> /* Needed for close() */
    #define SOCKET int;
    #define CROSSP_SOCKET_INVALID -1
#endif

#include <stdio.h>

#define PORT 8080

// gcc .\crossp_server.c -o .\bin\server.exe -lws2_32

int crossp_socket_init(void);
int crossp_socket_quit(void);
int crossp_socket_close(const SOCKET sock);
SOCKET crossp_socket_create(
    const int af, 
    const int type, 
    const int protocol, 
    const int level, 
    const int optname, 
    const char *optval, 
    const int optlen
);
struct sockaddr_in crossp_socket_create_addr(const unsigned short port, const unsigned long bind_addr);
int crossp_socket_bind(const SOCKET sock, const struct sockaddr_in *address);

int main(void) {
    char databuf[1024] = {0};
    
    crossp_socket_init(); 
    {
        // create a socket
        int opt = 1;
        SOCKET server_fd = crossp_socket_create(AF_INET, SOCK_STREAM, 0, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
        if (server_fd == CROSSP_SOCKET_INVALID) {
            printf("ERROR: Failed to create a socket!\n");
            exit(EXIT_FAILURE);
        }

        // create address and attaching socket to the port
        struct sockaddr_in addr = crossp_socket_create_addr(PORT, INADDR_ANY);
        if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            printf("ERROR: Failed to bind the socket!\n");
            exit(EXIT_FAILURE);
        }
    
    cleanup:
        crossp_socket_close(server_fd);
        
    }
    crossp_socket_quit();

    return 0;
}

int crossp_socket_init(void) {
    #ifdef _WIN32
        WSADATA wsa_data;
        return WSAStartup(MAKEWORD(2, 2), &wsa_data);
    #else
        return 0;
    #endif
}

int crossp_socket_quit(void) {
    #ifdef _WIN32
        return WSACleanup();
    #else
        return 0;
    #endif
}

int crossp_socket_close(const SOCKET sock) {
  int status = 0;

    #ifdef _WIN32
        status = shutdown(sock, SD_BOTH);
        if (status == 0) { status = closesocket(sock); }
    #else
        status = shutdown(sock, SHUT_RDWR);
        if (status == 0) { status = close(sock); }
    #endif

  return status;
}

SOCKET crossp_socket_create(const int af, const int type, const int protocol, const int level, const int optname, const char *optval, const int optlen) {
    // open socket file descriptor
    const SOCKET sock = socket(af, type, protocol);
    if (sock == CROSSP_SOCKET_INVALID) {
        return CROSSP_SOCKET_INVALID;
    }

    // Forcefully attaching socket to the port
    if (setsockopt(sock, level, optname, optval, optlen) < 0) {
        crossp_socket_close(sock);
        return CROSSP_SOCKET_INVALID;
    }

    return sock;
}

struct sockaddr_in crossp_socket_create_addr(const unsigned short port, const unsigned long bind_addr) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    #ifdef _WIN32
        addr.sin_addr.S_un.S_addr = bind_addr;
    #else
        addr.sin_addr.s_addr = bind_addr;
    #endif
    addr.sin_port = htons(port);
}

