#include <iostream>
#include <thread.hpp>
#include <socket.hpp>

int main()
{
    int x = 11223344;

    uint8_t buff[sizeof(int)];
    std::cout << "pack " << sizeof(int) << '\n';

    for (size_t i = 0; i < sizeof(int); i++)
    {
        buff[i] = (x >> (8 * i)) & 0xFF;
        std::cout << int(buff[i]) << '\n';
    }
    AppCommunication a = AppCommunication();
    a.open_socket();
    
    while(1){
        a.send_msg(buff, sizeof(int));
        std::cout << "send " << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    // auto p1 = Thread1();
    // auto p2 = Thread2();

    // Buffer *b = new Buffer();
    // std::thread t2(p1, std::ref(b));
    // std::thread t3(p2, std::ref(b));

    // t2.detach();
    // t3.join();

    // int x = 0;
    return 0;
}