#pragma once
#ifndef MATRIX_H  // защита от повторного включения
#define MATRIX_H

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Matrix {
private:
    int** data; 
    size_t rows;    
    size_t cols;   

public:
    // Конструкторы
    Matrix();
    Matrix(size_t r, size_t c);

    //Заполнение факториалами
    void setArrayFactorials();

    //Методы для работы с элементами массива
    int at(int i, int j) const;
    void setAt(int i, int j, int val);

    //ОПЕРАТОРЫ ИНКРЕМЕНТА И ДЕКРЕМЕНТА:

    // 1. Префиксный инкремент (++matrix)
    Matrix& operator++();

    // 2. Постфиксный инкремент (matrix++)
    // int в параметре - фиктивный параметр для отличия от префиксного
    Matrix operator++(int);

    // 3. Префиксный декремент (--matrix)
    Matrix& operator--();

    // 4. Постфиксный декремент (matrix--)
    Matrix operator--(int);

    //Форматирование чисел до нужной строковой ширины
    string formatToWidth(int value, int width = 8);
    //Геттеры
    const int* const* getData() const;
    size_t getRows() const;
    size_t getCols() const;

    // Метод для вывода
    void print();

    // Деструктор
    ~Matrix();
};

#endif // MATRIX_H