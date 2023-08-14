#include <socket.hpp>
#include <sys/select.h>
#include <thread>
#include <chrono>
#include <ctime>

int to_value(uint8_t *buffer, size_t len)
{
    int sum = 0;
    for (size_t i = 0; i < sizeof(uint); i++)
    {
        sum += (buffer[i] << (8 * i));
        std::clog << (int)buffer[i] << ' ' << (buffer[i] << (8 * i)) << '\n';
    }
    return sum;
}
void AppCommunicationClient::open_socket()
{
    serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un serverAddress;
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, socketPath);

    int connection = -1;
    uint8_t buffer[sizeof(uint)];

    while (true)
    {
        connection = connect(
            serverSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress));

        if (connection != 0)
            perror("connection failed");
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (connection < 0)
            continue;
        std::clog << "connected" << std::endl;
        int valread = -1;

        do
        {
            valread = read(serverSocket, buffer, sizeof(uint));
            if (valread == 0)
                break;

            std::clog << "[" << std::time(0) << "]" << valread << std::endl;
            std::cout << to_value(buffer, valread) << std::endl;
        } while (valread > 0);

        // recreate socket when server is disconnect
        if (valread == 0)
        {
            perror("disconnect: ");
            serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
        }
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