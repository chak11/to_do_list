cmake_minimum_required(VERSION 3.14)
project(to_do_list)

# Aggiunge GoogleTest dalla sotto-cartella
add_subdirectory(lib/googletest googletest-build)
include_directories(../lib/googletest/googletest/include)

# Lista dei test
set(SOURCE_TEST_FILES runToDoListTests.cpp ../Date.h ../Task.h ../TaskList.h ../Date.cpp ../Task.cpp ../TaskList.cpp
        DateTest.cpp)

# Crea l'eseguibile dei test
add_executable(runToDoListTests ${SOURCE_TEST_FILES} DateTest.cpp )

# Link con GoogleTest
target_link_libraries(runToDoListTests gtest gtest_main)
