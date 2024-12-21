#include "pentamino.h"

using namespace global;
TPoint SearchEmpty1(int Arr[62][62], TPoint st, TPoint end, int d) {
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

int CountEmpty(int y, int x, int Count) {
    if ((y < 0) || (x < 0)) return Count - 1;      //если вышли за диапазон, то выходим
    if (Pole[y][x] == 0)                       //если клетка пустая
    {
        if (Count == 4) return 5;                  //уже нашли 4-е, значит это пятая и выходим

        Pole[y][x] = 20;                          //указываем, что эту клетку сосчитали

        Count = CountEmpty(y, x + 1, Count + 1);   //переходим на соседнюю
        if (Count < 5)                             //если не нашли пять, то ищем дальше
        {
            Count = CountEmpty(y + 1, x, Count + 1);      //переходим на соседнюю
            if (Count < 5)                                //если не нашли пять, то ищем дальше
            {
                Count = CountEmpty(y, x - 1, Count + 1);     //переходим на соседнюю
                if (Count < 5)                               //если не нашли пять, то ищем дальше
                {
                    Count = CountEmpty(y - 1, x, Count + 1);   //переходим на соседнюю
                }
            }
        }
        Pole[y][x] = 0; //на выходе удаляем признак подсчета клетки
    } else return Count - 1;
    return Count; //выходим с найденным количеством
}

void delete_Figure(int i, int j, TPoint pt, TPoint f) {
    for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
        for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
            Pole[pt.y + y][pt.x - f.x + x] -= Shapes[i].Pieces[j].Arr[y][x];
        }
    }
}

bool checkFigure(Shape shape){
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (Pole[y][x] == shape.num){
                return true;
            }
        }
    }
    return false;
}

//основная функция поиска решения
void FindSolutions(int i) {
    TPoint pt(0, 0);
    int j = 0; // номер формы
    while (true) {
        if (checkFigure(Shapes[i])){
            i++;
        }
        //поиск пустой клетки на поле куда можно поставить текущую фигуру
        pt = SearchEmpty1(Pole, pt, TPoint(N, M), 0);

        // выход из цикла при выходе из диапазона
        if (pt.y == M) {
            break;
        }

        // пока не попробовали все повороты и отражения
        while (Shapes[i].count != j) {
            //поиск первой непустой клетки в фигуре по горизонтали
            TPoint f = SearchEmpty(Shapes[i].Pieces[j].Arr, TPoint(0, 0), TPoint(5, 5), i + 1);

            //пробуем вставлять, если выполняются условия, перебирая формы фигуры
            if (pt.x - f.x >= 0 && (pt.x - f.x) + Shapes[i].Pieces[j].LenX <= N &&
                pt.y + Shapes[i].Pieces[j].LenY <= M) {
                //вставка, если входит в границы
                bool s = true;

                //проверим можно ли вставить
                for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
                    for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
                        if (Shapes[i].Pieces[j].Arr[y][x] == i + 1)
                            if (Pole[pt.y + y][pt.x - f.x + x] != 0) {
                                s = false;
                                x = Shapes[i].Pieces[j].LenX; //выходим из циклов
                                y = Shapes[i].Pieces[j].LenY;
                            }
                    }
                }

                //вставляем
                if (s) {
                    for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
                        for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
                            Pole[pt.y + y][pt.x - f.x + x] += Shapes[i].Pieces[j].Arr[y][x];

                        }
                    }

                    //находим начальную точку для проверки на зажатость
                    int y1 = pt.y - 1;
                    int x1 = pt.x - f.x - 1;

                    //коррекция, чтобы не вылезть за диапазон
                    if (y1 < 0) y1 = 0;
                    if (x1 < 0) x1 = 0;

                    //проверка зажатой клетки
                    for (int y = y1; y < y1 + Shapes[i].Pieces[j].LenY + 2; y++) {
                        for (int x = x1; x < x1 + Shapes[i].Pieces[j].LenX + 2; x++) {
                            if (Pole[y][x] == 0) {
                                if (CountEmpty(y, x, 0) < 5) //если соседних клеток меньше 5-и, то
                                {
                                    s = false;
                                    x = N; //выходим из цикла, так как нашли место, которое нельзя уже ни чем заставить
                                    y = M;
                                }
                            }
                        }
                    }

                    if (s) { // если клетка не зажата
                        //если не все фигуры просмотрены, то продолжить искать
                        if (i < 11) {
                            FindSolutions(i + 1);
                            //удаление фигуры
                            delete_Figure(i, j, pt, f);
                            j++;

                        } else {
                            //проверка матрицы на заполнение
                            TPoint pr = pt;
                            pt = SearchEmpty1(Pole, TPoint(0, 0), TPoint(N, M), 0);

                            if (pt.x == 0 && pt.y == M) {
                                Solution++;
                                FILE_SAVE_s << " Решение : " << Solution << "\r\n";

                                //запись в файл
                                for (int y = 0; y < M; y++) {
                                    for (int x = 0; x < N; x++) {
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

                            //удаление фигуры
                            delete_Figure(i, j, pt, f);
                            j++;

                        }
                    } else {
                        //удаление фигуры
                        delete_Figure(i, j, pt, f);
                        j++;
                    }
                }//если не вставили
                else { j++; }
            }//если выходит за границы
            else { j++; }
        }//end while

        j = 0;

        // иначе сдвигаем на 1
        pt.x++;
        if (pt.x == N) {
            pt.x = 0;
            pt.y++;
            if (pt.y >= M) {
                break;
            }
        }
    }
}

void Start(std::string output_file, std::string input_file){
    FILE *f;
    char s[MAXLEN];
    FILE_SAVE_s.open(output_file);
    if ((f = fopen(input_file.c_str(), "r")) != NULL) {

        for (int y = 0; y < 62; y++) {
            for (int x = 0; x < 62; x++) {
                Pole[y][x] = -1;
            }
        }

        int k, l = 0, col = 0;
        M = 0;
        N = 0;

        while (!feof(f)) {
            fgets(s, MAXLEN, f);
            k = 0;
            while ((s[k] != 0) && (s[k] != '\n')) {\
                if (s[k] == '*') Pole[l][k] = 0;
                else if (s[k] > '0' && s[k] <= '9') Pole[l][k] = s[k] - 48;
                else if (s[k] > 'a' && s[k] <= 'c') Pole[l][k] = s[k] - 87;
                else if (s[k] != ' '){std::cout << "Wrong input data" << std::endl; return;}
                (s[k] != ' ') ? col++ : col;
                if (k > N) N = k;

                k++;
            }
            l++;
        }
        fclose(f);

        N++;
        M = l;

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