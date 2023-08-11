#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

#define MAX_BUFFER_LEN 64
#define ASCII_ZERO 48

class Buffer
{
public:
    enum class Status
    {
        cleared,
        in_process
    };
    Buffer();

    std::mutex *get_mutex() { return &_lock; }
    Status get_status() { return _status; }
    void set_status(Status s) { _status = s; }

    void write_to_buffer(std::string);
    std::string read_from_buffer();

    std::condition_variable cv;
    void show_buffer()
    {
        std::cout << _buffer << '\n';
    }

private:
    std::string _buffer;
    Status _status;
    std::mutex _lock;
};

class thread2
{
public:
    void operator()(Buffer *);

private:
    Buffer *b;
};

class thread1
{
public:
    void operator()(Buffer *);
    bool is_all_digit(std::string);
    void configure_string(std::string*);
private:
    Buffer *b;
};
