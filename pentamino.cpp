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

void delete_Figure(int i, int j, TPoint pt, TPoint f) {
    for (int y = 0; y < Shapes[i].Pieces[j].LenY; y++) {
        for (int x = 0; x < Shapes[i].Pieces[j].LenX; x++) {
            Pole[pt.y + y][pt.x - f.x + x] -= Shapes[i].Pieces[j].Arr[y][x];
        }
    }
}

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
                                FILE_SAVE_s << " Решение : " << Solution << "\r\n";

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

        // иначе сдвигаем на 1
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