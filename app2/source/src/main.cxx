#include <iostream>
#include <socket.hpp>


int main(){
    AppCommunicationClient a = AppCommunicationClient();
    a.open_socket();

    return 0;
}