cmake_minimum_required(VERSION 3.10.2)
project(exam_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(exam_list main.cpp list.h)

set(CMAKE_CXX_FLAGS "-pthread -Wall -std=c++14 -pedantic ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -D_GLIBCXX_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_COVERAGE "-g --coverage")
set(LINK_FLAGS "-pthread ${LINK_FLAGS}")

include_directories(.)
add_subdirectory(gtest)

add_library(counted counted.h counted.cpp fault_injection.h fault_injection.cpp list111.h)

add_executable(std std.cpp)
target_link_libraries(std counted gtest)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()