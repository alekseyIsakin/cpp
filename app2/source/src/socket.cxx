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

#ifdef DEBUG
        std::clog << (int)buffer[i] << ' ' << (buffer[i] << (8 * i)) << '\n';
#endif
    }
    return sum;
}
void Client::open_socket()
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
        {
#ifdef DEBUG
            perror("connection failed");
#endif
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        std::clog << "connected" << std::endl;
        int valread = -1;

        do
        {
            valread = read(serverSocket, buffer, sizeof(uint));
            if (valread == 0)
                break;
            int rec_value = to_value(buffer, valread);

#ifdef DEBUG
            std::clog << valread << ": " << rec_value << std::endl;
#endif
            if (rec_value > 9 && rec_value % 32 == 0)
                std::cout << "received value: " << rec_value << std::endl;
            else
                std::cout << "wrong value" << std::endl;

        } while (valread > 0);

        // recreate socket when server is disconnect
        if (valread == 0)
        {
            std::clog << "disconnect" << std::endl;
            serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
        }
    }
}

void Client::close_socket()
{
    close(serverSocket);
    unlink(socketPath);
}

Client::~Client()
{
    close_socket();
}