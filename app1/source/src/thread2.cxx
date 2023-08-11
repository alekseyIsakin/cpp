#include <thread.hpp>
#include <string>

#ifndef THREAD2
#define THREAD2

void Thread2::operator()(Buffer *new_b)
{
    b = new_b;
    auto m = b->get_mutex();

    while (true)
    {
        std::unique_lock<std::mutex> ul(*m);
        b->cv.wait(ul, [=]()
                   { return b->get_status() == Buffer::Status::in_process; });

        auto buffer = b->read_from_buffer();
        std::cout << "received string: " << buffer << '\n';

        int sum = 0;
        for (int i = 0; i < buffer.length(); i++)
        {
            if (std::isdigit(buffer[i]))
            {
                sum += buffer[i] - ASCII_ZERO;
            }
        }
        b->set_status(Buffer::Status::cleared);
        ul.unlock();
    }
}

#endif