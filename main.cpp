#include "pentamino.h"
using namespace global;

// указывать обязательную позицию для 1 фигуры

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
    Start(output_file, input_file);

    return 0;
}