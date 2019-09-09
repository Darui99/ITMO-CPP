//
// Created by darui99 on 30.05.19.
//

#include "decompressor.h"

decompressor::decompressor() {
    q = decryptor();
}

void decompressor::gen_codes(const std::vector<u_char> &tree_code, const std::vector<u_char> &perm) {
    std::vector <bool> bits, cur_code;
    for (unsigned char i : tree_code) {
        for (ptrdiff_t j = 7; j >= 0; j--)
            bits.push_back(((1 << j) & i) > 0);
    }
    size_t cur_num = 0;
    for (size_t i = 0; i < bits.size() - 1; i++) {
        if (bits[i] == 0)
            cur_code.push_back(0);
        else {
            q.add(cur_code, perm[cur_num]);
            cur_num++;
            while(!cur_code.empty() && cur_code.back() == 1)
                cur_code.pop_back();
            if (!cur_code.empty())
                cur_code.back() = 1;
        }
    }
}

std::vector<u_char> decompressor::decompress(u_char x, ptrdiff_t tail) {
    std::vector<u_char> res;
    for (ptrdiff_t j = 7; j > (7 - tail); j--) {
        q.go(((1 << j) & x) > 0);
        if (q.is_leaf())
            res.push_back(q.get_sym());
    }
    return res;
}