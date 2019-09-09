//
// Created by darui99 on 30.05.19.
//

#include "decryptor.h"

decryptor::decryptor() {
    trie.resize(1, Node());
    trie_ptr = 0;
}

void decryptor::add(const std::vector<bool> &arr, u_char sym) {
    size_t v = 0;
    for (bool i : arr) {
        size_t c = static_cast<size_t>(i);
        if (trie[v].next[c] != -1) {
            v = static_cast<size_t>(trie[v].next[c]);
        } else {
            trie[v].next[c] = trie.size();
            v = trie.size();
            trie.emplace_back();
        }
    }
    trie[v].term = true;
    trie[v].val = sym;
}

void decryptor::go(bool c) {
    trie_ptr = static_cast<size_t>(trie[trie_ptr].next[c]);
}

bool decryptor::is_leaf() const {
    return trie[trie_ptr].term;
}

u_char decryptor::get_sym() {
    u_char res = trie[trie_ptr].val;
    trie_ptr = 0;
    return res;
}