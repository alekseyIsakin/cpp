#include <iostream>
#include <thread.hpp>
#include <socket.hpp>

int main()
{
    int x = 11223344;

    uint8_t buff[sizeof(int)];
    std::cout << "pack " << sizeof(int) << '\n';

    // for (size_t i = 0; i < sizeof(int); i++)
    // {
    //     buff[i] = (x >> (8 * i)) & 0xFF;
    //     std::cout << int(buff[i]) << '\n';
    // }
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