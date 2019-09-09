//
// Created by darui99 on 30.05.19.
//

#ifndef HUFFMAN_FILE_DECOMPRESSOR_H
#define HUFFMAN_FILE_DECOMPRESSOR_H

#include "file_reader.h"
#include "file_writer.h"
#include "decompressor.h"
#include <queue>

struct file_decompressor {
    static void decompress_file (file_reader &scanner, file_writer &printer);

private:
    static const size_t ALPH_SIZE = 256;
};

#endif //HUFFMAN_FILE_DECOMPRESSOR_H
