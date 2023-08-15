#include <iostream>
#include <thread.hpp>
#include <signal.h>
#include <socket_server.hpp>


int main()
{
    std::clog << "start" << std::endl;

#ifdef DEBUG
    std::clog << "Debug mode" << std::endl;
#endif

    // Handle broken pipe Signal
    struct sigaction sa;
    sa.sa_handler = broken_pipe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGPIPE, &sa, 0) == -1)
    {
        perror(0);
        exit(1);
    }

    Server::get_instance()->open_socket();

    auto p1 = Thread1();
    auto p2 = Thread2();

    std::thread t1(p1);
    std::thread t2(p2);

    t1.join();
    t2.join();

    Server::get_instance()->close_socket();
    return 0;
}