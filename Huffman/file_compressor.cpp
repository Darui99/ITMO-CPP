//
// Created by darui99 on 30.05.19.
//

#include "file_compressor.h"

void file_compressor::compress_file(file_reader &scanner1, file_reader &scanner2, file_writer &printer) {
    compressor q = compressor();

    u_char cur;
    while (scanner1.has_next()) {
        cur = scanner1.next();
        q.add_char(cur);
    }

    try {
        q.compress();
        printer.put(q.get_tree_code());
        for (size_t i = 0; i < ALPH_SIZE; i++)
            printer.put(q.get_sym_by_num(i));

        while (scanner2.has_next()) {
            cur = scanner2.next();
            printer.put(q.get_code(static_cast<size_t>(cur)));
        }
    } catch (...) {
        throw std::runtime_error("Compressing failed.");
    }
}