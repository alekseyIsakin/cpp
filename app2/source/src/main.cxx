#include <iostream>
#include <socket.hpp>


int main(){
    std::cout << "Hello World" << std::endl;
    AppCommunicationClient a = AppCommunicationClient();
    a.open_socket();
    // uint8_t buff[sizeof(int)];
    // int num = 0;

    // std::cout << "unpack " << sizeof(int) <<std::endl;
    // for (size_t i = 0; i < sizeof(int); i++)
    // {
    //     num += (buff[i] << (8 * i));
    //     std::cout << int(buff[i]) << " " << (buff[i] << (8 * i)) << std::endl;
    // }
    // std::cout << num << std::endl;

    return 0;
}