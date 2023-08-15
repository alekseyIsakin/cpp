#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <mode.hpp>

#define PORT 8080

#ifndef APP_SOCKET
#define APP_SOCKET

class Client
{
public:
    const char* socketPath = "/tmp/test_app.socket";
    void open_socket();
    void close_socket();
    void send_msg(const uint8_t*, size_t);
    ~Client();
private:
    int serverSocket = -1;
};

#endif