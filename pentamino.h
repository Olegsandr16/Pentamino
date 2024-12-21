#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAXLEN 100

/**
 * @file pentamino.h
 * @brief Header файл проекта
 */

/**
 * @brief Структура в которой хранятся координаты определенной точки
 * @param x координата по x
 * @param y координата по y
 */


typedef struct TPoint {
    int x;
    int y;

    TPoint(int a, int b) {
        x = a;
        y = b;
    }
} TPoint;

/**
 * @brief Структура, с помощью которой описывается фигура
 * @param LenX длина по x
 * @param LenY длина по y
 * @param Arr[5][5] массив, хранящий координаты фигуры
 */
struct Piece {
public:
    int LenX, LenY;
    int Arr[5][5];
};

/**
 * @brief Структура, хранящая все вариации фигуры с учетом поворотов и отражений, количество этих вариаций и номер фигуры от 1 до 12
 * @param Pieces хранит все описания фигуры с помощью структуры Piece
 * @param count количество вариаций фигуры
 * @param num номер фигуры от 1 до 12
 */
struct Shape {
    Piece Pieces[8];
    int count;
    int num;
};

/**
 * @brief Класс, описывающий переменные, использующиеся как глобальные
 * @param height максимальная ширина поля
 * @param width максимальная длина поля
 * @param solution количество решений
 * @param pole игровое поле
 * @param output_file выходной файл, куда сохраняется результат работы программы
 * @param shapes[12] 12 фигур со всевозможными их вариациями
 */
class Variables{
public:
    static int width, height, solution;
    static std::vector<std::vector<int>> pole;
    static std::ofstream output_file;
    static Shape shapes[12];

};

/**
 * @brief Функция начала логической части программы
 * @param output_file имя выходного файла
 * @param input_file имя входного файла
 */
void start(std::string output_file, std::string input_file);