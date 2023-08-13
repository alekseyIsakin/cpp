#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080

#ifndef APP_SOCKET
#define APP_SOCKET

class AppCommunicationServer
{
public:
    enum class Status
    {
        connected,
        disconnected
    };
    const char *socketPath = "/tmp/test_app.socket";
    void open_socket();
    void close_socket();
    int try_connect();
    bool is_connected() { return recv(clientSocket, nullptr, 1, 0) > -1; }
    void send_msg(const uint8_t *, size_t);
    ~AppCommunicationServer();

    Status get_status() { return _connect_flag; }

private:
    int clientSocket = -1;
    int serverSocket = -1;
    Status _connect_flag = Status::disconnected;
    struct sockaddr_un clientAddress;
    socklen_t clientAddressSize;
};

#endif