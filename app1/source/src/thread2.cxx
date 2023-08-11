#include <thread.hpp>

#ifndef THREAD2
#define THREAD2

void thread2::operator()(Buffer *new_b)
{
    b = new_b;
    auto m = b->get_mutex();

    while (true)
    {
        std::unique_lock<std::mutex> ul(*m);
        b->cv.wait(ul, [=]()
                   { return b->get_status() == Buffer::Status::in_process; });

        auto s = b->read_from_buffer();
        std::cout << "received string: " << s << '\n';

        b->set_status(Buffer::Status::cleared);
        ul.unlock();
    }
}

#endif