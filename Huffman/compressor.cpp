//
// Created by darui99 on 30.05.19.
//

#include "compressor.h"

compressor::compressor() {
    cnt.resize(ALPH_SIZE);
    code.resize(ALPH_SIZE);
    perm.resize(ALPH_SIZE);
}

void compressor::add_char(u_char x) {
    cnt[x]++;
}

void compressor::compress() {
    q = encryptor(cnt);
    q.encrypt(code, tree_code, perm);
}

std::vector<bool> const & compressor::get_code(size_t ind) const {
    return code[ind];
}

std::vector<bool> const & compressor::get_tree_code() const {
    return tree_code;
}

u_char compressor::get_sym_by_num(size_t ind) const {
    return perm[ind];
}