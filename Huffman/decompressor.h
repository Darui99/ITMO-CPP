//
// Created by darui99 on 27.05.19.
//

#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include "decryptor.h"

class decompressor {
    decryptor q;

public:
    decompressor();

    void gen_codes(const std::vector<u_char> &tree_code, const std::vector<u_char> &perm);

    std::vector<u_char> decompress(u_char x, ptrdiff_t tail);
};

#endif //HUFFMAN_DECOMPRESSOR_H