cmake_minimum_required(VERSION 3.10)
set(HEADER_FILES_s include/socket.hpp)

project(app2)
add_library(socket src/socket.cxx ${HEADER_FILES_s})

add_executable(app2 src/main.cxx)
target_link_libraries(app2 PUBLIC socket)

target_include_directories(socket PUBLIC include)
