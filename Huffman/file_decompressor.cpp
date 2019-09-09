//
// Created by darui99 on 30.05.19.
//

#include "file_decompressor.h"

void file_decompressor::decompress_file (file_reader &scanner, file_writer &printer) {
    decompressor q = decompressor();

    u_char cur;
    std::vector<u_char> tree_code, perm(ALPH_SIZE);

    try {
        for (size_t i = 0; i < 64; i++) {
            if (!scanner.has_next()) {
                throw std::runtime_error("Decompressing failed. Source file is incorrect.");
            }
            tree_code.push_back(scanner.next());
        }
        for (size_t i = 0; i < ALPH_SIZE; i++) {
            if (!scanner.has_next()) {
                throw std::runtime_error("Decompressing failed. Source file is incorrect.");
            }
            perm[i] = scanner.next();
        }

        q.gen_codes(tree_code, perm);

        std::queue<u_char> que;
        std::vector<u_char> decompressed_sym;
        while (scanner.has_next()) {
            cur = scanner.next();
            if (que.size() >= 3) {
                decompressed_sym = q.decompress(que.front(), 8);
                que.pop();
                for (unsigned char i : decompressed_sym)
                    printer.put(i);
            }
            que.push(cur);
        }
        while (que.size() > 2) {
            decompressed_sym = q.decompress(que.front(), 8);
            que.pop();
            for (unsigned char i : decompressed_sym)
                printer.put(i);
        }
        if (que.size() < 2)
            return;
        cur = que.front();
        que.pop();
        decompressed_sym = q.decompress(cur, que.front());
        que.pop();
        for (unsigned char i : decompressed_sym)
            printer.put(i);
    } catch (...) {
        throw std::runtime_error("Decompressing failed. Source file is incorrect.");
    }
}