#include <iostream>
#include <cstring>
#include <string>
#include "tasks.h"
using namespace std;

// Задание 2. Вариант 2
//2D → 1D.Двумерный массив 5х5 целых чисел необходимо выложить
//в один ряд по элементам слева направо и сверху вниз, исключая все элементы на
//четных строках.
//Инициализация: заполнить массив факториалами : x[i][j] = (i + j)!.
//Вывод на экран : на каждый элемент массива отвести 8 позиций.

int task2() {
    int a[5][5];

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            int f = 1;
            for (int k = 1; k <= i + j; k++)
                f = f * k;
            a[i][j] = f;
        }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    return 0;
}