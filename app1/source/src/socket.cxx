#include <socket_server.hpp>
#include <sys/select.h>

void AppCommunicationServer::open_socket()
{
    serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un serverAddress;
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, socketPath);

    // Unlink the socket path if it already exists (clean-up)
    unlink(socketPath);

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 1);

    clientAddressSize = sizeof(clientAddress);
}

int AppCommunicationServer::try_connect()
{

    fd_set readfds;
    fd_set writefds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(serverSocket, &readfds);
    FD_SET(serverSocket, &writefds);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int s = select(serverSocket + 1, &readfds, &writefds, nullptr, &timeout);
    if (s > 0)
    {
        if (FD_ISSET(serverSocket, &readfds) || FD_ISSET(serverSocket, &writefds))
        {
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
            std::cout << "obtain client socket" << std::endl;
            _connect_flag = Status::connected;
            return 0;
        }
    }
    else if (s == 0)
    {
        std::cout << "Timeout: No connection within 10 seconds." << std::endl;
    }
    else
    {
        perror("Select error");
    }
    _connect_flag = Status::connected;
    return -1;
}

void AppCommunicationServer::send_msg(const uint8_t *buff, size_t len)
{
    char buffer[1024];

    if (get_status() == Status::disconnected)
    {
        perror("connection");
        try_connect();

        if (get_status() == Status::disconnected)
        {
            return;
        }
    }

    if (int sended = send(clientSocket, buff, len, 0) < 0)
    {
        perror("send status");
        _connect_flag = Status::disconnected;
    }
}

void AppCommunicationServer::close_socket()
{
    close(clientSocket);
    close(serverSocket);
    unlink(socketPath);
}

AppCommunicationServer::~AppCommunicationServer()
{
    close_socket();
}