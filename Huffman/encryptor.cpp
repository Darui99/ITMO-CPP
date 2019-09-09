//
// Created by darui99 on 30.05.19.
//

#include "encryptor.h"

void encryptor::build_tree() {
    std::set<std::pair<size_t, size_t> > q;
    std::vector<u_char> perm(ALPH_SIZE);

    for (size_t i = 0; i < ALPH_SIZE; i++) {
        q.insert(std::make_pair(cnt[i], i));
    }

    while (q.size() > 1) {
        std::pair<size_t, size_t> first, second;
        auto it = q.begin();
        first = *it;
        q.erase(it);
        it = q.begin();
        second = *it;
        q.erase(it);
        q.insert(std::make_pair(first.first + second.first, g.size()));
        g.push_back(std::vector<size_t>(2));
        g.back()[0] = first.second;
        g.back()[1] = second.second;
    }
}

void encryptor::generate_codes(size_t v, std::vector < std::vector<bool> > &code, std::vector<bool> &tree_code, std::vector<u_char> &perm) {
    for (size_t i = 0; i < g[v].size(); i++) {
        size_t to = g[v][i];
        if (i == 0) {
            tree_code.push_back(0);
            cur_code.push_back(0);
        } else {
            cur_code.push_back(1);
        }
        generate_codes(to, code, tree_code, perm);
        cur_code.pop_back();
    }
    if (g[v].empty()) {
        code[v] = cur_code;
        perm[num++] = static_cast<u_char>(v);
        tree_code.push_back(1);
    }
}

encryptor::encryptor() {
    cnt = std::vector<size_t>(ALPH_SIZE);
    g.resize(ALPH_SIZE);
    num = 0;
}

encryptor::encryptor(const std::vector<size_t> &arr) {
    cnt = arr;
    g.resize(ALPH_SIZE);
    num = 0;
}

void encryptor::encrypt(std::vector < std::vector<bool> > &code, std::vector<bool> &tree_code, std::vector<u_char> &perm) {
    build_tree();
    generate_codes(g.size() - 1, code, tree_code, perm);
    tree_code.push_back(0);
}