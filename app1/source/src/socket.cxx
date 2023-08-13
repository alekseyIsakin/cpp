#include <socket_server.hpp>
#include <sys/select.h>

#define SUCCESS_CONNECT 1
#define TIMEOUT -1
#define OTHER 0

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
    timeout.tv_sec = 0;
    timeout.tv_usec = 5e4;

    int s = select(serverSocket + 1, &readfds, &writefds, nullptr, &timeout);
    if (s > 0)
    {
        if (FD_ISSET(serverSocket, &readfds) || FD_ISSET(serverSocket, &writefds))
        {
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
            _connect_flag = Status::connected;
            return SUCCESS_CONNECT;
        }
    }
    else if (s == 0)
    {
        return TIMEOUT;
    }
    return OTHER;
}

void AppCommunicationServer::send_msg(const uint8_t *buff_s, size_t len)
{
    auto reconnect = [this](std::string msg) -> int
    {
        // std::cout
        std::clog
            << "try connect... " << std::flush;

        auto connect = try_connect();
        if (connect != SUCCESS_CONNECT)
        {
            // std::cout
            std::clog
                << ((connect == TIMEOUT) ? "timeout" : "select error")
                << std::endl;
            return connect;
        }
        else
        {
            // std::cout
            std::clog
                << "success" << std::endl;
        }
    };

    if (get_status() == Status::disconnected)
    {
        if (reconnect("try connect... ") != SUCCESS_CONNECT)
            return;
    }

    auto st = get_status();

    if (auto sended = send(clientSocket, buff_s, len, 0) < 0)
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

AppCommunicationServer::AppCommunicationServer() {}
AppCommunicationServer::~AppCommunicationServer()
{
    close_socket();
}

void broken_pipe_handler(int signal)
{
    AppCommunicationServer::get_instance()
        ->set_status(AppCommunicationServer::Status::disconnected);
}

AppCommunicationServer *AppCommunicationServer::instancePtr = NULL;
