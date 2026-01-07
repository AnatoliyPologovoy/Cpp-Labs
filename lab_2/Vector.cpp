#include <iostream>
#include <cstring>
#include <string>
#include "Vector.h"  // подключаем наш заголовочный файл
using namespace std;

Vector::Vector() : data(nullptr), size(0) {
    cout << "Создан пустой одномерный массив" << endl;
}

Vector::Vector(size_t s) {
    size = s;
    data = new int[s];
    cout << "Создан одномерный массив размером " << s << endl;

};

//Заполнение массива элементами из нечетных строк двумерного массива
void Vector::setByOddRows2DArr(int** array2D, size_t rows, size_t cols) {
    //считаем кол-во нечетных строк
    size_t oddRowsCount = 0;
    for (size_t i = 1; i <= rows; i++) {
        if (i % 2 != 0) {  // если нечётная (1, 3)
            oddRowsCount++;
        }
    }
    //Освобождаем старую память (если была)
    if (data != nullptr) {
        delete[] data;
    }

    data = new int[oddRowsCount * cols];
    size = oddRowsCount * cols;

    size_t index1DArr = 0;  // индекс в одномерном массиве

    for (size_t i = 0; i < rows; i++) {
        size_t realRowCount = i + 1; //Смещение нумерации строк на обычный манер по которому строилась задача
        if (realRowCount % 2 != 0) {  // если строка нечётная
            for (size_t j = 0; j < cols; j++) {
                data[index1DArr] = array2D[i][j];
                index1DArr++;
            }
        }
    }
};

void Vector::print() {
    cout << "[ ";
    for (size_t i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << "]";
    cout << endl;
};

Vector::~Vector() {
    delete[] data;
    cout << "Удалён массив размером " << size << endl;
};
