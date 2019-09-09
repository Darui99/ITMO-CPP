//
// Created by darui99 on 30.05.19.
//

#include "file_writer.h"

void file_writer::write_buffer() {
    fwrite (buf, 1, buffer_ptr, output);
    buffer_ptr = 0;
}

void file_writer::add_bit(bool bit) {
    if (bit)
        last |= (1 << (7 - last_sz));
    last_sz++;
    if (last_sz == 8) {
        put(last);
        last_sz = 0;
        last = 0;
    }
}

file_writer::file_writer(const char* file_name, bool type) {
    buffer_ptr = 0;
    last = 0;
    last_sz = 0;
    output = fopen(file_name, "wb");
    if (output == nullptr)
        throw std::runtime_error(std::string(file_name) + " is unavailable");
    coder = type;
}

file_writer::~file_writer() {
    if (coder) {
        if (last_sz > 0) {
            put(last);
            put(static_cast<u_char>(last_sz));
        } else {
            put(static_cast<u_char>(8));
        }
    }
    if (buffer_ptr > 0)
        write_buffer();
    fclose(output);
}

void file_writer::put(u_char x) {
    if (buffer_ptr >= BUF_SIZE)
        write_buffer();
    buf[buffer_ptr++] = x;
}

void file_writer::put(const std::vector<bool> & bits) {
    for (bool bit : bits)
        add_bit(bit);
}
