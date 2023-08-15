#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <socket_server.hpp>
#include <mode.hpp>

#define MAX_BUFFER_LEN 64
#define ASCII_ZERO 48

#ifndef THREADS
#define THREADS
class Buffer
{
public:
    static Buffer *get_instance()
    {
        if (instancePtr == nullptr)
        {
            instancePtr = new Buffer();
        }
        return instancePtr;
    };
    Buffer(const Buffer &obj) = delete;

public:
    enum class Status
    {
        cleared,
        in_process
    };

    std::mutex *get_mutex() { return &_lock; }
    Status get_status() { return _status; }
    void set_status(Status s) { _status = s; }

    void write_to_buffer(std::string);
    std::string read_from_buffer();

    std::condition_variable cv;
    void show_buffer() { std::cout << _buffer << std::endl; }

private:
    Buffer();

private:
    std::string _buffer;
    Status _status;
    std::mutex _lock;

    static Buffer *instancePtr;
};

class Thread2
{
public:
    Thread2();
    void operator()();

private:
    Buffer *b;
    Server *a;
};

class Thread1
{
public:
    Thread1();
    void operator()();
    bool is_all_digit(std::string);
    std::string configure_string(std::string *);

private:
    Buffer *b;
};

#endif