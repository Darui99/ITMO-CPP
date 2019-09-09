//
// Created by darui99 on 27.05.19.
//

#ifndef HUFFMAN_DECRYPTOR_H
#define HUFFMAN_DECRYPTOR_H

#include <iostream>
#include <vector>
#include <cstddef>

class decryptor {
    struct Node {
        ptrdiff_t next[2];
        u_char val;
        bool term;

        Node() {
            next[0] = next[1] = -1;
            term = false;
        }
    };

    std::vector <Node> trie;
    size_t trie_ptr;

public:
    decryptor();

    void add(const std::vector<bool> &arr, u_char sym);

    void go(bool c);

    bool is_leaf() const;

    u_char get_sym();
};

#endif //HUFFMAN_DECRYPTOR_H