

#include <socket.hpp>

#ifndef SOCKET
#define SOCKET

void AppCommunication::open_socket()
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
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    std::cout << "obtain client socket" << '\n';
}

void AppCommunication::send_msg(const uint8_t *buff, size_t len)
{
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << clientSocket << ' ' << rand()%10 << ' ' << bytesRead << '\n';

    if (bytesRead > 0){
        int res = send(clientSocket, buff, len, 0);
    }
    else
    {
        close_socket();
        open_socket();
    }
}

void AppCommunication::close_socket()
{
    close(clientSocket);
    close(serverSocket);
    unlink(socketPath);
}

AppCommunication::~AppCommunication()
{
    close_socket();
}

#endif