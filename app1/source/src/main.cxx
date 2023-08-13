#include <iostream>
#include <thread.hpp>
#include <signal.h>
#include <socket_server.hpp>

int main()
{
    AppCommunicationServer*a = AppCommunicationServer::get_instance();
    Buffer b = Buffer();

    struct sigaction sa;
    sa.sa_handler = broken_pipe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGPIPE, &sa, 0) == -1)
    {
        perror(0);
        exit(1);
    }
    a->open_socket();

    auto p1 = Thread1(&b);
    auto p2 = Thread2(&b, a);

    std::thread t2(p1);
    std::thread t3(p2);

    t2.detach();
    t3.join();

    a->close_socket();
    return 0;
}