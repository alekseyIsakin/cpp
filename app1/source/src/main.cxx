#include <iostream>
#include <thread.hpp>
#include <socket_server.hpp>

int main()
{
    AppCommunicationServer a = AppCommunicationServer();
    Buffer b = Buffer();
    a.open_socket();

    auto p1 = Thread1(&b);
    auto p2 = Thread2(&b, &a);

    std::thread t2(p1);
    std::thread t3(p2);

    t2.detach();
    t3.join();

    a.close_socket();
    return 0;
}