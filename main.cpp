#include "pentamino.h"

/**
 * @file main.cpp
 * @brief Начальный файл
 * @namespace global
 * @author Yushchenko ALexander 2354
 */

///@brief считывает имена входного и выходного файлов и запускает функцию Start
int main(int argc, char *argv[]) {

    std::string input_file;
    std::string output_file;

    if (argc == 3) {
        input_file = argv[1];
        output_file = argv[2];
    } else {
        input_file = "../input.txt";
        output_file = "../output.txt";
    }
    start(output_file, input_file);

    return 0;
}