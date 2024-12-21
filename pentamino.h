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
 * @brief Описание глобальных переменных
 * @namespace global
 * @param Width максимальная ширина поля
 * @param Height максимальная длина поля
 * @param Solution количество решений
 * @param Pole начальное поле типа std::vector<std::vector<int>>
 * @param FILE_SAVE_s выходной файл, куда сохраняется результат работы программы
 * @param Shapes[12] 12 фигур со всевозможными их вариациями
 */
namespace global {
    extern int Width, Height, Solution;
    extern std::vector<std::vector<int>> Pole;
    extern std::ofstream FILE_SAVE_s;
    extern Shape Shapes[12];
}
/**
 * @brief Функция поиска решений
 * @param i индекс данной фигуры
 */
void FindSolutions(int i);

/**
 * @brief Функция начала логической части программы
 * @param output_file имя выходного файла
 * @param input_file имя входного файла
 */
void Start(std::string output_file, std::string input_file);