cmake_minimum_required(VERSION 3.13)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(huffman_lib STATIC
        compressor.cpp
        compressor.h
        decompressor.cpp
        decompressor.h
        decryptor.cpp
        decryptor.h
        encryptor.cpp
        encryptor.h)

add_executable(Huffman
    file_compressor.cpp
    file_compressor.h
    file_decompressor.cpp
    file_decompressor.h
    file_reader.cpp
    file_reader.h
    file_writer.cpp
    file_writer.h
    main.cpp)

    target_link_libraries(Huffman huffman_lib)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined,leak -D_GLIBCXX_DEBUG")
