//
// Created by darui99 on 27.05.19.
//

#ifndef HUFFMAN_FILE_READER_H
#define HUFFMAN_FILE_READER_H

#include <iostream>
#include <string>

class file_reader {
    static const size_t BUF_SIZE = 2048;
    u_char buf[BUF_SIZE];
    size_t buffer_ptr, bytes_read;
    FILE* input;

    void fill_buffer();

public:
    file_reader(const char* file_name);

    ~file_reader();

    u_char next();

    bool has_next();
};

#endif //HUFFMAN_FILE_READER_H
