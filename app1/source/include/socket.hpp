#include <sys/socket.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

#ifndef APP_SOCKET
#define APP_SOCKET

class AppCommunication
{
public:
    const char* socketPath = "/tmp/test_app.socket";
    void open_socket();
    void close_socket();
    void send_msg(const uint8_t*, size_t);
    ~AppCommunication();
private:
    int clientSocket = -1;
    int serverSocket = -1;
    struct sockaddr_un clientAddress;
    socklen_t clientAddressSize;

};

#endif