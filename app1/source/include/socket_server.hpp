#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include <mode.hpp>

#define PORT 8080

#ifndef APP_SOCKET
#define APP_SOCKET

void broken_pipe_handler(int signal);

class Server
{
public:
    static Server *get_instance()
    {
        if (instancePtr == nullptr)
        {
            instancePtr = new Server();
        }
        return instancePtr;
    };
    Server(const Server &obj) = delete;

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

    Status get_status() { return _connect_flag; }
    void set_status(Status new_status) { _connect_flag = new_status; }

private:
    ~Server();
    Server();
    int clientSocket = -1;
    int serverSocket = -1;
    struct sockaddr_un clientAddress;
    socklen_t clientAddressSize;

    Status _connect_flag = Status::disconnected;
    static Server *instancePtr;
};


#endif