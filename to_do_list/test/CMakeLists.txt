cmake_minimum_required(VERSION 3.14)
project(to_do_list)

add_subdirectory(lib/googletest googletest-build)
include_directories(../lib/googletest/googletest/include)

set(SOURCE_TEST_FILES runToDoListTests.cpp ../SubTask.h ../SubTask.cpp ../Date.h ../Task.h ../TaskList.h ../Date.cpp ../Task.cpp ../TaskList.cpp
        DateTest.cpp)

add_executable(runToDoListTests ${SOURCE_TEST_FILES} DateTest.cpp TaskTest.cpp TaskListTest.cpp SubTaskTest.cpp)

target_link_libraries(runToDoListTests gtest gtest_main)
