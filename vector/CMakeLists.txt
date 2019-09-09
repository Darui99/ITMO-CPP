cmake_minimum_required(VERSION 3.13)
project(vector)

set(CMAKE_CXX_STANDARD 17)

add_executable(vector_testing
        vector_testing.cpp
        counted.h
        counted.cpp
        fault_injection.h
        fault_injection.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)

add_executable(vector_testing1488
        vector.h
        main.cpp
        counted.h
        counted.cpp
        fault_injection.h
        fault_injection.cpp
        gtest/gtest-all.cc
        gtest/gtest.h)


#add_executable(vector main.cpp vector.h counted.h counted.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(vector_testing -lpthread)
target_link_libraries(vector_testing1488 -lpthread)