#include <iostream>
#include <thread.hpp>
#include <socket.hpp>

int main()
{
    AppCommunication a = AppCommunication();
    Buffer b = Buffer();

    auto p1 = Thread1(&b);
    auto p2 = Thread2(&b, &a);

    std::thread t2(p1);
    std::thread t3(p2);

    t2.detach();
    t3.join();

    return 0;
}