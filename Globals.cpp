#include "pentamino.h"
namespace global {
    int M, N, Solution = 0;
    int Pole[62][62];
    std::ofstream FILE_SAVE_s;

    Shape Shapes[12] =
            {
                    //  #
                    // ###
                    //  #
                    {{3, 3, {{0, 1, 0, 0, 0}, {1, 1, 1, 0, 0}, {0,                 1,                   0,               0,               0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}}, 1, 1},
                    // #####
                    {{
                      {5, 1, {{2,  2,  2,  2,  2}, {0, 0,  0,  0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {1, 5, {{2, 0,  0, 0, 0}, {2,  0,  0, 0, 0}, {2,  0,  0, 0, 0}, {2,  0,  0, 0, 0}, {2, 0, 0, 0, 0}}}
                     },                                                                                                                                                           2, 2},
                    // #
                    // ###
                    //   #
                    {{
                      {3, 3, {{3,  0,  0,  0,  0}, {3, 3,  3,  0,  0}, {0, 0, 3, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {3, 3, {{0, 3,  3, 0, 0}, {0,  3,  0, 0, 0}, {3,  3,  0, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               3,               {{3,  3,  0, 0, 0}, {0,  3,  0,  0,  0}, {0, 3, 3, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{0,  0,  3, 0, 0}, {3,  3,  3, 0, 0}, {3,  0, 0, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           4, 3},
                    // ###
                    // #
                    // #
                    {{
                      {3, 3, {{4,  4,  4,  0,  0}, {4, 0,  0,  0,  0}, {4, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {3, 3, {{4, 4,  4, 0, 0}, {0,  0,  4, 0, 0}, {0,  0,  4, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               3,               {{0,  0,  4, 0, 0}, {0,  0,  4,  0,  0}, {4, 4, 4, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{4,  0,  0, 0, 0}, {4,  0,  0, 0, 0}, {4,  4, 4, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           4, 4},
                    //  ##
                    // ##
                    // #
                    {{
                      {3, 3, {{0,  5,  5,  0,  0}, {5, 5,  0,  0,  0}, {5, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {3, 3, {{5, 5,  0, 0, 0}, {0,  5,  5, 0, 0}, {0,  0,  5, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               3,               {{0,  0,  5, 0, 0}, {0,  5,  5,  0,  0}, {5, 5, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{5,  0,  0, 0, 0}, {5,  5,  0, 0, 0}, {0,  5, 5, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           4, 5},
                    // ###
                    //  #
                    //  #
                    {{
                      {3, 3, {{6,  6,  6,  0,  0}, {0, 6,  0,  0,  0}, {0, 6, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {3, 3, {{0, 0,  6, 0, 0}, {6,  6,  6, 0, 0}, {0,  0,  6, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               3,               {{0,  6,  0, 0, 0}, {0,  6,  0,  0,  0}, {6, 6, 6, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{6,  0,  0, 0, 0}, {6,  6,  6, 0, 0}, {6,  0, 0, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           4, 6},
                    // ###
                    // # #
                    {{
                      {3, 2, {{7,  7,  7,  0,  0}, {7, 0,  7,  0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {2, 3, {{7, 7,  0, 0, 0}, {0,  7,  0, 0, 0}, {7,  7,  0, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               2,               {{7,  0,  7, 0, 0}, {7,  7,  7,  0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 3, {{7,  7,  0, 0, 0}, {7,  0,  0, 0, 0}, {7,  7, 0, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           4, 7},
                    // #
                    // ###
                    //  #
                    {{
                      {3, 3, {{8,  0,  0,  0,  0}, {8, 8,  8,  0,  0}, {0, 8, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {3, 3, {{0, 8,  8, 0, 0}, {8,  8,  0, 0, 0}, {0,  8,  0, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               3,               {{0,  8,  0, 0, 0}, {8,  8,  8,  0,  0}, {0, 0, 8, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{0,  8,  0, 0, 0}, {0,  8,  8, 0, 0}, {8,  8, 0, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{8,  8, 0, 0, 0}, {0,  8,  8, 0, 0}, {0,  8,  0, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{0, 8,  0,  0,  0}, {8,  8,  8,  0,  0}, {8, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{0,  8,  0, 0, 0}, {8,  8,  0, 0, 0}, {0, 8,  8, 0, 0}, {0, 0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 3, {{0,  0,  8,  0,  0}, {8,  8,  8, 0, 0}, {0, 8, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           8, 8},
                    // ####
                    //    #
                    {{
                      {4, 2, {{9,  9,  9,  9,  0}, {0, 0,  0,  9,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {2, 4, {{0, 9,  0, 0, 0}, {0,  9,  0, 0, 0}, {0,  9,  0, 0, 0}, {9,  9,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {4,               2,               {{9,  0,  0, 0, 0}, {9,  9,  9,  9,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{9,  9,  0, 0, 0}, {9,  0,  0, 0, 0}, {9,  0, 0, 0, 0}, {9,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{9,  0, 0, 0, 0}, {9,  0,  0, 0, 0}, {9,  0,  0, 0, 0}, {9,  9,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {4, 2, {{0, 0,  0,  9,  0}, {9,  9,  9,  9,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{9,  9,  0, 0, 0}, {0,  9,  0, 0, 0}, {0, 9,  0, 0, 0}, {0, 9,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {4, 2, {{9,  9,  9,  9,  0}, {9,  0,  0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           8, 9},
                    // ####
                    //   #
                    {{
                      {4, 2, {{10, 10, 10, 10, 0}, {0, 0,  10, 0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {2, 4, {{0, 10, 0, 0, 0}, {0,  10, 0, 0, 0}, {10, 10, 0, 0, 0}, {0,  10, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {4,               2,               {{0,  10, 0, 0, 0}, {10, 10, 10, 10, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{10, 0,  0, 0, 0}, {10, 10, 0, 0, 0}, {10, 0, 0, 0, 0}, {10, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{10, 0, 0, 0, 0}, {10, 0,  0, 0, 0}, {10, 10, 0, 0, 0}, {10, 0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {4, 2, {{0, 0,  10, 0,  0}, {10, 10, 10, 10, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{0,  10, 0, 0, 0}, {10, 10, 0, 0, 0}, {0, 10, 0, 0, 0}, {0, 10, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {4, 2, {{10, 10, 10, 10, 0}, {0,  10, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           8, 10},
                    // ###
                    //   ##
                    {{
                      {4, 2, {{11, 11, 11, 0,  0}, {0, 0,  11, 11, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {2, 4, {{0, 11, 0, 0, 0}, {0,  11, 0, 0, 0}, {11, 11, 0, 0, 0}, {11, 0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {4,               2,               {{11, 11, 0, 0, 0}, {0,  11, 11, 11, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{0,  11, 0, 0, 0}, {11, 11, 0, 0, 0}, {11, 0, 0, 0, 0}, {11, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{11, 0, 0, 0, 0}, {11, 0,  0, 0, 0}, {11, 11, 0, 0, 0}, {0,  11, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {4, 2, {{0, 0,  11, 11, 0}, {11, 11, 11, 0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 4, {{11, 0,  0, 0, 0}, {11, 11, 0, 0, 0}, {0, 11, 0, 0, 0}, {0, 11, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {4, 2, {{0,  11, 11, 11, 0}, {11, 11, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           8, 11},
                    // ###
                    //  ##
                    {{
                      {3, 2, {{12, 12, 12, 0,  0}, {0, 12, 12, 0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                         {2, 3, {{0, 12, 0, 0, 0}, {12, 12, 0, 0, 0}, {12, 12, 0, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                            {3,               2,               {{12, 12, 0, 0, 0}, {12, 12, 12, 0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 3, {{12, 12, 0, 0, 0}, {12, 12, 0, 0, 0}, {12, 0, 0, 0, 0}, {0,  0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 3, {{12, 0, 0, 0, 0}, {12, 12, 0, 0, 0}, {12, 12, 0, 0, 0}, {0,  0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 2, {{0, 12, 12, 0,  0}, {12, 12, 12, 0,  0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {2, 3, {{12, 12, 0, 0, 0}, {12, 12, 0, 0, 0}, {0, 12, 0, 0, 0}, {0, 0,  0, 0, 0}, {0, 0, 0, 0, 0}}},
                             {3, 2, {{12, 12, 12, 0,  0}, {12, 12, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}}
                     },                                                                                                                                                           8, 12}

            };
}