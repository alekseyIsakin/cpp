#include <thread.hpp>
#include <socket_server.hpp>
#include <string>

Thread2::Thread2(Buffer *new_b, AppCommunicationServer *new_a)
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

        uint sum = 0;
        for (int i = 0; i < buffer.length(); i++)
        {
            if (std::isdigit(buffer[i]))
            {
                sum += buffer[i] - ASCII_ZERO;
            }
        }
        std::cout << "string: " << buffer << std::endl;
        std::clog << "string: " << buffer  << ", sum: " << sum << std::endl;
        b->set_status(Buffer::Status::cleared);
        ul.unlock();

        // Pack sum
        uint8_t buff[sizeof(uint)] = {0};
        
        for (size_t i = 0; i < sizeof(uint); i++)
        {
            buff[i] = (sum >> (8 * i)) & 0xFF;
            std::clog << (int)buff[i] << " ";
        }
        std::clog << std::endl;

        a->send_msg(buff, sizeof(int));
    }
}