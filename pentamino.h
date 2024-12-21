#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#define MAXLEN 100

typedef struct TPoint {
    int x;
    int y;

    TPoint(int a, int b) {
        x = a;
        y = b;
    }
} TPoint;

struct Piece {
public:
    int LenX, LenY;
    int Arr[5][5];
};

struct Shape {
    Piece Pieces[8];
    int count;
    int num;
};

namespace global {
    extern int N, M, Solution;
    extern int Pole[62][62];
    extern std::ofstream FILE_SAVE_s;
    extern Shape Shapes[12];
}

void FindSolutions(int i);
void Start(std::string output_file, std::string input_file);