#include <thread.hpp>
#include <cctype>
#include <algorithm>
Thread1::Thread1()
{
    b = Buffer::get_instance();
}

void Thread1::operator()()
{
    auto m = b->get_mutex();

    while (true)
    {
        std::string s = "";
        std::cin >> s;

#ifdef DEBUG
        std::clog << "input: " << s << std::endl;
#endif
        if (s == "q")
        {
            exit(0);
        }
        if (s.length() <= MAX_BUFFER_LEN && is_all_digit(s))
        {
            //
            std::lock_guard<std::mutex> lg(*m);
            s = configure_string(&s);
            b->write_to_buffer(s);
            b->set_status(Buffer::Status::in_process);
            b->cv.notify_all();
        }
        else
        {
            std::cout << "string is`nt correct" << std::endl;
        }
    }
}

std::string Thread1::configure_string(std::string *buffer)
{
    std::string new_buffer;
    std::sort(buffer->begin(), buffer->end(), std::greater<int>());
    char even[] = {'K', 'B'};
    for (int i = 0; i < buffer->length(); i++)
    {
        if ((*buffer)[i] % 2 == 0)
        {
            new_buffer.append("KB");
        }
        else
        {
            new_buffer.insert(new_buffer.end(), (*buffer).at(i));
        }
    }
    return new_buffer;
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