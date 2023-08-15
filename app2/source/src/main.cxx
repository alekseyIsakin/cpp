#include <iostream>
#include <socket.hpp>



int main()
{
    std::clog << "start" << std::endl;
    Client a = Client();
    a.open_socket();

    return 0;
}