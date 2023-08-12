#include <thread.hpp>

Buffer::Buffer()
{
    _status = Status::cleared;
    for (int i = 0; i < MAX_BUFFER_LEN; i++)
    {
        _buffer[i] = 0;
    }
}

void Buffer::write_to_buffer(std::string s)
{
    _buffer = s;
}

std::string Buffer::read_from_buffer()
{
    std::string s = _buffer;
    _buffer.clear();
    return s;
}