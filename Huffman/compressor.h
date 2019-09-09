//
// Created by darui99 on 27.05.19.
//

#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include "encryptor.h"

class compressor {
    std::vector<size_t> cnt;
    std::vector < std::vector<bool> > code;
    std::vector<bool> tree_code;
    std::vector<u_char> perm;
    encryptor q;

public:
    compressor();

    void add_char(u_char x);

    void compress();

    std::vector<bool> const & get_code(size_t ind) const;

    std::vector<bool> const & get_tree_code() const;

    u_char get_sym_by_num(size_t ind) const;
};

#endif //HUFFMAN_COMPRESSOR_H
