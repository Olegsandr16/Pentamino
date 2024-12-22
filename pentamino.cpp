#include <filesystem>
#include "pentamino.h"


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

TPoint searchEmptyArea(std::vector<std::vector<int>> Arr, TPoint st, TPoint end, int d) {
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
TPoint searchEmptyBlock(int Arr[5][5], TPoint st, TPoint end, int d) {
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
int countEmptyPoints(int y, int x, int Count) {
    if ((y < 0) || (x < 0)) return Count - 1;
    if (Variables::pole[y][x] == 0)
    {
        if (Count == 4) return 5;

        Variables::pole[y][x] = 20;

        Count = countEmptyPoints(y, x + 1, Count + 1);
        if (Count < 5)
        {
            Count = countEmptyPoints(y + 1, x, Count + 1);
            if (Count < 5)
            {
                Count = countEmptyPoints(y, x - 1, Count + 1);
                if (Count < 5)
                {
                    Count = countEmptyPoints(y - 1, x, Count + 1);
                }
            }
        }
        Variables::pole[y][x] = 0;
    } else return Count - 1;
    return Count;
}

/**
 * @brief Удаляет фигуру с поля
 * @param i индекс фигуры в массиве Variables::shapes
 * @param j индекс конкретного варианта (поворот или отражение) фигуры с индексом i
 * @param pt объект типа TPoint, представляющий координаты (y, x) левого верхнего угла размещения фигуры на поле
 * @param f Объект типа TPoint,  представляющий смещение относительно левого верхнего угла фигуры до ее первой заполненной ячейки.
 * Это необходимо, потому что фигура может иметь "дырки" или не начинаться с (0, 0)
 */
void deleteFigure(int i, int j, TPoint pt, TPoint f) {
    for (int y = 0; y < Variables::shapes[i].Pieces[j].LenY; y++) {
        for (int x = 0; x < Variables::shapes[i].Pieces[j].LenX; x++) {
            Variables::pole[pt.y + y][pt.x - f.x + x] -= Variables::shapes[i].Pieces[j].Arr[y][x];
        }
    }
}

/**
 * @brief Проверяет есть ли фигура уже на поле(Необходимо, если во входных данных задается конкретное местоположение одной из фигур
 * @param shape объект типа Shape, содержащий в себе всю информацию о данной фигуре
 */
bool checkFigure(Shape shape){
    for (int y = 0; y < Variables::height; y++) {
        for (int x = 0; x < Variables::width; x++) {
            if (Variables::pole[y][x] == shape.num){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Функция поиска решений
 * @param i индекс данной фигуры в переменной Variables::shapes
 */
void findSolutions(int i) {
    TPoint pt(0, 0);
    int j = 0;
    while (true) {
        if (checkFigure(Variables::shapes[i])){
            i++;
        }

        //!поиск пустой клетки на поле куда можно поставить текущую фигуру
        pt = searchEmptyArea(Variables::pole, pt, TPoint(Variables::width, Variables::height), 0);

        if (pt.y == Variables::height) {
            break;
        }

        //! пока не попробовали все повороты и отражения
        while (Variables::shapes[i].count != j) {
            TPoint f = searchEmptyBlock(Variables::shapes[i].Pieces[j].Arr, TPoint(0, 0), TPoint(5, 5), i + 1);

            if (pt.x - f.x >= 0 && (pt.x - f.x) + Variables::shapes[i].Pieces[j].LenX <= Variables::width && pt.y + Variables::shapes[i].Pieces[j].LenY <= Variables::height) {
                //! вставка, если входит в границы
                bool s = true;

                //! проверим можно ли вставить фигуру в поле
                for (int y = 0; y < Variables::shapes[i].Pieces[j].LenY; y++) {
                    for (int x = 0; x < Variables::shapes[i].Pieces[j].LenX; x++) {
                        if (Variables::shapes[i].Pieces[j].Arr[y][x] == i + 1)
                            if (Variables::pole[pt.y + y][pt.x - f.x + x] != 0) {
                                s = false;
                                x = Variables::shapes[i].Pieces[j].LenX;
                                y = Variables::shapes[i].Pieces[j].LenY;
                            }
                    }
                }
                //! вставляем фигуру в поле
                if (s) {
                    for (int y = 0; y < Variables::shapes[i].Pieces[j].LenY; y++) {
                        for (int x = 0; x < Variables::shapes[i].Pieces[j].LenX; x++) {
                            Variables::pole[pt.y + y][pt.x - f.x + x] += Variables::shapes[i].Pieces[j].Arr[y][x];

                        }
                    }
                    //! находим начальную точку для проверки на зажатость
                    int y1 = pt.y - 1;
                    int x1 = pt.x - f.x - 1;

                    //! коррекция, чтобы не вылезть за диапазон
                    if (y1 < 0) y1 = 0;
                    if (x1 < 0) x1 = 0;

                    //!проверка зажатой клетки
                    for (int y = y1; y < y1 + Variables::shapes[i].Pieces[j].LenY + 2; y++) {
                        for (int x = x1; x < x1 + Variables::shapes[i].Pieces[j].LenX + 2; x++) {
                            if (Variables::pole[y][x] == 0) {
                                if (countEmptyPoints(y, x, 0) < 5)
                                {//! нашли место, которое нельзя уже ни чем заставить
                                    s = false;
                                    x = Variables::width;
                                    y = Variables::height;
                                }
                            }
                        }
                    }

                    if (s) {
                        //! если не все фигуры просмотрены, то продолжить искать
                        if (i < 11) {
                            findSolutions(i + 1);
                            deleteFigure(i, j, pt, f);
                            j++;

                        } else {
                            //! проверка матрицы на заполнение
                            TPoint pr = pt;
                            pt = searchEmptyArea(Variables::pole, TPoint(0, 0), TPoint(Variables::width, Variables::height), 0);

                            if (pt.x == 0 && pt.y == Variables::height) {
                                Variables::solution++;
                                Variables::output_file << "Решение : " << Variables::solution << "\r\n";

                                //! вывод поля и запись в файл
                                for (int y = 0; y < Variables::height; y++) {
                                    for (int x = 0; x < Variables::width; x++) {
                                        char c = (char) (Variables::pole[y][x] + 0x30);
                                        if (Variables::pole[y][x] < 0) c = ' ';
                                        if (Variables::pole[y][x] > 9)
                                            c = (char) (Variables::pole[y][x] - 10 + 'a');
                                        Variables::output_file << " " << c;
                                    }
                                    Variables::output_file << "\r\n";
                                }
                            }
                            pt = pr;

                            deleteFigure(i, j, pt, f);
                            j++;

                        }
                    } else {
                        deleteFigure(i, j, pt, f);
                        j++;
                    }
                }
                else j++;
            }
            else j++;
        }

        j = 0;

        pt.x++;
        if (pt.x == Variables::width) {
            pt.x = 0;
            pt.y++;
            if (pt.y >= Variables::height) {
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
void start(std::string output_file, std::string input_file){
    FILE *f;
    char s[MAXLEN];
    Variables::output_file.open(output_file);
    f = fopen(input_file.c_str(), "r");
    if (f != NULL) {

        for (int y = 0; y < 62; y++) {
            Variables::pole.push_back({});
            for (int x = 0; x < 62; x++) {
                Variables::pole[y].push_back(-1);
            }
        }

        int k, l = 0, col = 0;
        Variables::height = 0;
        Variables::width = 0;

        while (!feof(f)) {
            fgets(s, MAXLEN, f);
            k = 0;
            while ((s[k] != 0) && (s[k] != '\n')) {\
                if (s[k] == '*') Variables::pole[l][k] = 0;
                else if (s[k] > '0' && s[k] <= '9') Variables::pole[l][k] = s[k] - 48;
                else if (s[k] > 'a' && s[k] <= 'c') Variables::pole[l][k] = s[k] - 87;
                else if (s[k] != ' '){std::cout << "Wrong input data" << std::endl; return;}
                (s[k] != ' ') ? col++ : col;
                if (k > Variables::width) Variables::width = k;

                k++;
            }
            l++;
        }
        fclose(f);

        Variables::width++;
        Variables::height = l;

        if (col == 60) {
            std::cout << "Finding solutions . . .\n";
            findSolutions(0);
            std::cout << "Finish . . .\n"
                         "Result in " << output_file << std::endl;
        } else {
            std::cout << "Square of rectangle != 60\n";
        }

    } else {
        std::cout << "Input file is not opened";
    }

    if(!Variables::output_file.tellp())
        Variables::output_file << "Решений нет" << std::endl;

    Variables::output_file.close();
    return;
}