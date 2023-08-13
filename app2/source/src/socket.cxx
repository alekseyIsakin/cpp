#include <socket.hpp>
#include <sys/select.h>
#include <thread>
#include <chrono>
#include <ctime>

void AppCommunicationClient::open_socket()
{
    serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un serverAddress;
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, socketPath);

    int connection = -1;
    while (connection == -1)
    {
        connection = connect(
            serverSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        perror("connect status");
    }

    while (true)
    {
        uint8_t buffer[1024];
        int valread = read(serverSocket, buffer, 1024);

        int i = 0;

        std::cout << "[" << std::time(0) << "]" << valread << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));


    }
}

void AppCommunicationClient::close_socket()
{
    // close(clientSocket);
    // close(serverSocket);
    // unlink(socketPath);
}

AppCommunicationClient::~AppCommunicationClient()
{
    close_socket();
}