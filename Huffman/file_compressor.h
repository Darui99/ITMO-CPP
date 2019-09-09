//
// Created by darui99 on 30.05.19.
//

#ifndef HUFFMAN_FILE_COMPRESSOR_H
#define HUFFMAN_FILE_COMPRESSOR_H

#include "file_reader.h"
#include "file_writer.h"
#include "compressor.h"

struct file_compressor {
    static void compress_file(file_reader &scanner1, file_reader &scanner2, file_writer &printer);
};

#endif //HUFFMAN_FILE_COMPRESSOR_H
