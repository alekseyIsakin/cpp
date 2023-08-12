#include <socket.hpp>
#include <sys/select.h>

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

    fd_set readfds;
    fd_set writefds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(serverSocket, &readfds);
    FD_SET(serverSocket, &writefds);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int s = select(serverSocket+1, &readfds, &writefds, nullptr, &timeout);
    if (s > 0)
    {
        if (FD_ISSET(serverSocket, &readfds) || FD_ISSET(serverSocket, &writefds))
        {
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
            std::cout << "obtain client socket" << '\n';
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
}

void AppCommunication::send_msg(const uint8_t *buff, size_t len)
{
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "try send data [" << bytesRead << "]" << '\n';

    if (bytesRead > 0)
    {
        int res = send(clientSocket, buff, len, 0);
        std::cout << "send " << res << '\n';

    }
    else
    {
        std::cout << "connection is closed, reopen" << '\n';
        close_socket();
        open_socket();
        int res = send(clientSocket, buff, len, 0);
        std::cout << "send "<< res << '\n';
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