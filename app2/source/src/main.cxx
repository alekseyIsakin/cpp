#include <iostream>
#include <socket.hpp>


int main(){
    std::cout << "Hello World" << std::endl;
    AppCommunicationClient a = AppCommunicationClient();
    a.open_socket();

    return 0;
}