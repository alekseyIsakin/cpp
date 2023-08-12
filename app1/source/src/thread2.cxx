#include <thread.hpp>
#include <socket.hpp>
#include <string>

Thread2::Thread2(Buffer *new_b, AppCommunication *new_a)
{
    b = new_b;
    a = new_a;
}

void Thread2::operator()()
{
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

        // Pack sum
        uint8_t buff[sizeof(int)];
        for (size_t i = 0; i < sizeof(int); i++)
        {
            buff[i] = (sum >> (8 * i)) & 0xFF;
            std::cout << int(buff[i]) << '\n';
        }
        a->send_msg(buff, sizeof(int));
    }
}