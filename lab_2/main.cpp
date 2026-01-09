// main.cpp
#include <iostream>
#include "Vector.h"
#include "Matrix.h" 
#include "Fraction.h"
#include <windows.h>
#include "Shop.h"
using namespace std;

void task1() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ ЗАДАНИЯ 1 (Вариант 2) ===" << endl;
    cout << "=========================================" << endl << endl;

    // Тестовые данные
    const size_t ROWS = 5;
    const size_t COLS = 5;

    cout << "1. Создаём двумерный массив " << ROWS << "x" << COLS << endl;
    Matrix matrix(ROWS, COLS);
    matrix.setArrayFactorials(); //Заполняем факториалами
    matrix.print();

    cout << "\n2. Создаём пустой вектор, потом заполняем элементами из 2D массива:" << endl;
    cout << "--------------------------------------" << endl;

    // 2 Создаём пустой вектор, потом заполняем из 2D массива
    Vector vector;
    cout << "   До заполнения: ";
    vector.print();
    vector.setByOddRows2DArr(matrix.getData(), matrix.getRows(), matrix.getCols());

    cout << "   После заполнения из нечётных строк: ";
    vector.print();


    cout << "\n3.Тесты at() и setAt()\n\n";

    Matrix m(2, 2);

    m.setAt(0, 0, 10);
    m.setAt(0, 1, 20);
    m.setAt(1, 0, 30);
    m.setAt(1, 1, 40);

    cout << "Матрица после setAt:\n";
    m.print();
    cout << "\nm.at(1,0) = " << m.at(1, 0);

}

int main() {
    SetConsoleOutputCP(1251);  // Windows-1251 для русского

    task1(); //Демонстрация задания 1
    // 
    //Демонстрация класса Fraction (задание 2)
    //demonstrateFractionClass();

    //Демонстрация класса Shop (задание 3)
    //demonstrateShopClass();
        
    return 0;
}