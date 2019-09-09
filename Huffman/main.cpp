#include "file_compressor.h"
#include "file_decompressor.h"
#include <string>

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << "Numbers of arguments must be 3 (mode, name of source file, name of destination file).\n";
        return 0;
    }

    //double start = clock();

    if (std::string(argv[1]) == "-c") {
        try {
            file_reader scanner1 = file_reader(argv[2]);
            file_reader scanner2 = file_reader(argv[2]);
            file_writer printer = file_writer(argv[3], true);

            file_compressor::compress_file(scanner1, scanner2, printer);
        } catch (std::runtime_error const e) {
            std::cout << e.what() << '\n';
        }

    } else if (std::string(argv[1]) == "-d") {
        try {
            file_reader scanner = file_reader(argv[2]);
            file_writer printer = file_writer(argv[3], false);

            file_decompressor::decompress_file(scanner, printer);
        } catch (std::runtime_error const e) {
            std::cout << e.what() << '\n';
        }

    } else {
        std::cout << R"(Incorrect mode (it must be "-c" for compressing or "-d" for decompressing.\n)";
    }

    //std::cout << std::fixed << (clock() - start) / CLOCKS_PER_SEC << '\n';

    return 0;
}