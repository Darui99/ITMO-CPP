//
// Created by darui99 on 27.05.19.
//

#ifndef HUFFMAN_ENCRYPTOR_H
#define HUFFMAN_ENCRYPTOR_H

#include <iostream>
#include <vector>
#include <set>

const size_t ALPH_SIZE = 256;

class encryptor {
    std::vector<size_t> cnt;
    std::vector < std::vector<size_t> > g;
    std::vector<bool> cur_code;
    size_t num;

    void build_tree();

    void generate_codes(size_t v, std::vector < std::vector<bool> > &code, std::vector<bool> &tree_code, std::vector<u_char> &perm);

public:
    encryptor();

    encryptor(const std::vector<size_t> &arr);

    void encrypt(std::vector < std::vector<bool> > &code, std::vector<bool> &tree_code, std::vector<u_char> &perm);
};

#endif //HUFFMAN_ENCRYPTOR_H
