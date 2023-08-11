#include <iostream>
#include <thread>
#include <thread.hpp>

int main(){
    std::cout << "Hellos world\n";

    auto p1 = thread1();
    auto p2 = thread2();
    Buffer *b = new Buffer();
    std::thread t2(p1, std::ref(b));
    std::thread t3(p2, std::ref(b));

    t2.detach();
    t3.join();

    int x = 0;
    return 0;
}