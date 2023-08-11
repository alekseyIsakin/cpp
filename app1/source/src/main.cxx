#include <iostream>
#include <thread>
#include <thread.hpp>

int main(){
    auto p1 = Thread1();
    auto p2 = Thread2();
    Buffer *b = new Buffer();
    std::thread t2(p1, std::ref(b));
    std::thread t3(p2, std::ref(b));

    t2.detach();
    t3.join();

    int x = 0;
    return 0;
}