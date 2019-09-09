//
// Created by darui99 on 30.05.19.
//

#include "file_reader.h"

void file_reader::fill_buffer() {
    buffer_ptr = 0;
    bytes_read = fread(buf, 1, BUF_SIZE, input);
    if (bytes_read == 0) {
        if (ferror(input) > 0)
            throw std::runtime_error("Read error");
    }
}

file_reader::file_reader(const char* file_name) {
    buffer_ptr = 0;
    bytes_read = 0;
    input = fopen(file_name, "r");
    if (input == nullptr)
        throw std::runtime_error(std::string(file_name) + " is unavailable");
}

file_reader::~file_reader() {
    fclose(input);
}

u_char file_reader::next() {
    if (buffer_ptr >= bytes_read)
        fill_buffer();
    return buf[buffer_ptr++];
}

bool file_reader::has_next() {
    if (buffer_ptr >= bytes_read)
        fill_buffer();
    return (buffer_ptr < bytes_read);
}
