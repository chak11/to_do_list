cmake_minimum_required(VERSION 3.14)
project(to_do_list)

set(CMAKE_CXX_STANDARD 17)

add_executable(task_manager main.cpp Date.h Date.cpp Task.h Task.cpp TaskList.h TaskList.cpp)
