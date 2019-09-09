//
// Created by darui99 on 27.05.19.
//

#ifndef HUFFMAN_FILE_WRITER_H
#define HUFFMAN_FILE_WRITER_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <string>

class file_writer {
    static const size_t BUF_SIZE = 2048;
    u_char buf[BUF_SIZE], last;
    size_t buffer_ptr, last_sz;
    FILE* output;
    bool coder;

    void write_buffer();

    void add_bit(bool bit);

public:
    file_writer(const char* file_name, bool type);

    ~file_writer();

    void put(u_char x);

    void put(const std::vector<bool> & bits);
};

#endif //HUFFMAN_FILE_WRITER_H
