#include <thread.hpp>
#include <cctype>
#include <algorithm>

#ifndef THREAD1
#define THREAD1

void Thread1::operator()(Buffer *new_b)
{
    b = new_b;

    auto m = b->get_mutex();

    while (true)
    {
        std::string s = "";
        std::cout << ">> ";
        std::cin >> s;

        if (s.length() <= MAX_BUFFER_LEN && is_all_digit(s))
        {
            //
            std::lock_guard<std::mutex> lg(*m);
            configure_string(&s);
            b->write_to_buffer(s);
            b->set_status(Buffer::Status::in_process);
            b->cv.notify_all();
        }
    }
}

void Thread1::configure_string(std::string *buffer)
{
    std::sort(buffer->begin(), buffer->end(), std::greater<int>());
    char even[] = {'K', 'B'};
    for (int i = 0; i < buffer->length(); i++)
    {
        if ((*buffer)[i] % 2 == 0)
        {
            (*buffer)[i] = even[std::rand() % 2];
        }
    }
}

bool Thread1::is_all_digit(std::string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (std::isdigit(s[i]) == false)
            return false;
    }
    return true;
}

#endif