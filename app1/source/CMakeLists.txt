cmake_minimum_required(VERSION 3.10)
set(HEADER_FILES_t include/thread.hpp)
set(HEADER_FILES_s include/socket_server.hpp)

project(app1)
add_library(threads src/buffer.cxx src/thread1.cxx src/thread2.cxx ${HEADER_FILES_t})
add_library(socket src/socket.cxx ${HEADER_FILES_s})
add_executable(app1 src/main.cxx)

target_link_libraries(app1 PUBLIC threads)
target_link_libraries(app1 PUBLIC socket)

target_include_directories(threads PUBLIC include)
target_include_directories(socket PUBLIC include)
target_include_directories(app1 PUBLIC include)