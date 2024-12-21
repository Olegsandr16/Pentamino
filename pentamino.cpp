#include "pentamino.h"

using namespace global;

/**
 * @file pentamino.cpp
 * @brief Файл со всеми функциями проекта
 */

/**
 * @brief Определяет клетку заданного типа на всем поле после заданной клетки
 * @param Arr игровое поле
 * @param st стартовая точка
 * @param end конечная точка
 * @param d искомое значение
 */
TPoint SearchEmpty1(std::vector<std::vector<int>> Arr, TPoint st, TPoint end, int d) {
    for (; st.y < end.y; st.y++) {
        for (; st.x < end.x; st.x++) {
            if (Arr[st.y][st.x] == d) {
                return st;
            }
        }
        st.x = 0;
    }
    return st;
}

/**
 * @brief Определяет клетку заданного типа на поле 5х5 после заданной клетки
 * @param Arr поле 5х5
 * @param st стартовая точка
 * @param end конечная точка
 * @param d искомое значение
 */
TPoint SearchEmpty(int Arr[5][5], TPoint st, TPoint end, int d) {
    for (; st.y < end.y; st.y++) {
        for (; st.x < end.x; st.x++) {
            if (Arr[st.y][st.x] == d) {
                return st;
            }
        }
        st.x = 0;
    }
    return st;
}

/**
 * @brief Определяет наличие хотя бы пяти свободных клеток после заданной
 * @param y координата по оси y
 * @param x координата по оси x
 * @param Count счетчик свободных клеток
 */
int CountEmpty(int y, int x, int Count) {
    if ((y < 0) || (x < 0)) return Count - 1;
    if (Pole[y][x] == 0)
    {
        if (Count == 4) return 5;

        Pole[y][x] = 20;

        Count = CountEmpty(y, x + 1, Count + 1);
        if (Count < 5)
        {
            Count = CountEmpty(y + 1, x, Count + 1);
            if (Count < 5)
            {
                Count = CountEmpty(y, x - 1, Count + 1);
                if (Count < 5)
                {
                    Count = CountEmpty(y - 1, x, Count + 1);
                }
            }
        }
        Pole[y][x] = 0;
    } else return Count - 1;
    return Count;
}

/**
 * @brief Удаляет фигуру с поля
 * @param i индекс фигуры в массиве Shapes
 * @param j индекс конкретного варианта (поворот или отражение) фигуры с индексом i
 * @param pt объект типа TPoint, представляющий координаты (y, x) левого верхнего угла размещения фигуры на поле
 * @param f Объект типа TPoint,  представляющий смещение относительно левого верхнего угла фигуры до ее первой заполненной ячейки.
 * Это необходимо, потому что фигура может иметь "дырки" или не начинаться с (0, 0)
 */
void delete_Figure(int i, int j, TPoint pt, TPoint f) {
    for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
        for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
            Pole[pt.y + y][pt.x - f.x + x] -= Shapes[i].Pieces[j].Arr[y][x];
        }
    }
}

/**
 * @brief Проверяет есть ли фигура уже на поле(Необходимо, если во входных данных задается конкретное местоположение одной из фигур
 * @param shape объект типа Shape, содержащий в себе всю информацию о данной фигуре
 */
bool checkFigure(Shape shape){
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            if (Pole[y][x] == shape.num){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Функция поиска решений
 * @param i индекс данной фигуры в переменной Shapes
 */
void FindSolutions(int i) {
    TPoint pt(0, 0);
    int j = 0;
    while (true) {
        if (checkFigure(Shapes[i])){
            i++;
        }
        pt = SearchEmpty1(Pole, pt, TPoint(Width, Height), 0);

        if (pt.y == Height) {
            break;
        }

        while (Shapes[i].count != j) {
            TPoint f = SearchEmpty(Shapes[i].Pieces[j].Arr, TPoint(0, 0), TPoint(5, 5), i + 1);

            if (pt.x - f.x >= 0 && (pt.x - f.x) + Shapes[i].Pieces[j].LenX <= Width &&
                pt.y + Shapes[i].Pieces[j].LenY <= Height) {
                bool s = true;

                for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
                    for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
                        if (Shapes[i].Pieces[j].Arr[y][x] == i + 1)
                            if (Pole[pt.y + y][pt.x - f.x + x] != 0) {
                                s = false;
                                x = Shapes[i].Pieces[j].LenX; //������� �� ������
                                y = Shapes[i].Pieces[j].LenY;
                            }
                    }
                }

                if (s) {
                    for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
                        for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
                            Pole[pt.y + y][pt.x - f.x + x] += Shapes[i].Pieces[j].Arr[y][x];

                        }
                    }

                    int y1 = pt.y - 1;
                    int x1 = pt.x - f.x - 1;

                    if (y1 < 0) y1 = 0;
                    if (x1 < 0) x1 = 0;

                    for (int y = y1; y < y1 + Shapes[i].Pieces[j].LenY + 2; y++) {
                        for (int x = x1; x < x1 + Shapes[i].Pieces[j].LenX + 2; x++) {
                            if (Pole[y][x] == 0) {
                                if (CountEmpty(y, x, 0) < 5)
                                {
                                    s = false;
                                    x = Width;
                                    y = Height;
                                }
                            }
                        }
                    }

                    if (s) {
                        if (i < 11) {
                            FindSolutions(i + 1);
                            delete_Figure(i, j, pt, f);
                            j++;

                        } else {
                            TPoint pr = pt;
                            pt = SearchEmpty1(Pole, TPoint(0, 0), TPoint(Width, Height), 0);

                            if (pt.x == 0 && pt.y == Height) {
                                Solution++;
                                FILE_SAVE_s << "Решение : " << Solution << "\r\n";

                                for (int y = 0; y < Height; y++) {
                                    for (int x = 0; x < Width; x++) {
                                        char c = (char) (Pole[y][x] + 0x30);
                                        if (Pole[y][x] < 0) c = ' ';
                                        if (Pole[y][x] > 9)
                                            c = (char) (Pole[y][x] - 10 + 'a');
                                        FILE_SAVE_s << " " << c;
                                    }
                                    FILE_SAVE_s << "\r\n";
                                }
                            }
                            pt = pr;

                            delete_Figure(i, j, pt, f);
                            j++;

                        }
                    } else {
                        delete_Figure(i, j, pt, f);
                        j++;
                    }
                }
                else j++;
            }
            else j++;
        }

        j = 0;

        pt.x++;
        if (pt.x == Width) {
            pt.x = 0;
            pt.y++;
            if (pt.y >= Height) {
                break;
            }
        }
    }
}
/**
 * @brief Функция начала логической части программы
 * @param output_file имя выходного файла
 * @param input_file имя входного файла
 */
void Start(std::string output_file, std::string input_file){
    FILE *f;
    char s[MAXLEN];
    FILE_SAVE_s.open(output_file);
    if ((f = fopen(input_file.c_str(), "r")) != NULL) {

        for (int y = 0; y < 62; y++) {
            Pole.push_back({});
            for (int x = 0; x < 62; x++) {
                Pole[y].push_back(-1);
            }
        }

        int k, l = 0, col = 0;
        Height = 0;
        Width = 0;

        while (!feof(f)) {
            fgets(s, MAXLEN, f);
            k = 0;
            while ((s[k] != 0) && (s[k] != '\n')) {\
                if (s[k] == '*') Pole[l][k] = 0;
                else if (s[k] > '0' && s[k] <= '9') Pole[l][k] = s[k] - 48;
                else if (s[k] > 'a' && s[k] <= 'c') Pole[l][k] = s[k] - 87;
                else if (s[k] != ' '){std::cout << "Wrong input data" << std::endl; return;}
                (s[k] != ' ') ? col++ : col;
                if (k > Width) Width = k;

                k++;
            }
            l++;
        }
        fclose(f);

        Width++;
        Height = l;

        if (col == 60) {
            std::cout << "Finding solutions . . .\n";
            FindSolutions(0);
            std::cout << "Writting in file . . .\n";
        } else {
            std::cout << "Square of rectangle != 60\n";
        }

    } else {
        std::cout << "File is Null";
    }
    FILE_SAVE_s.close();
    return;
}