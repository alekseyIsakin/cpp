#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <socket.hpp>


#define MAX_BUFFER_LEN 64
#define ASCII_ZERO 48

#ifndef THREADS
#define THREADS
class Buffer
{
public:
    enum class Status
    {
        cleared,
        in_process
    };
    Buffer();

    std::mutex* get_mutex() { return &_lock; }
    Status get_status() { return _status; }
    void set_status(Status s) { _status = s; }

    void write_to_buffer(std::string);
    std::string read_from_buffer();

    std::condition_variable cv;
    void show_buffer() { std::cout << _buffer << '\n'; }

private:
    std::string _buffer;
    Status _status;
    std::mutex _lock;
};



class Thread2
{
public:
    Thread2(Buffer*, AppCommunication*);
    void operator()();

private:
    Buffer* b;
    AppCommunication* a;
};



class Thread1
{
public:
    Thread1(Buffer *);
    void operator()();
    bool is_all_digit(std::string);
    void configure_string(std::string*);
private:
    Buffer *b;
};

#endif