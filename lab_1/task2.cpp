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

//Заполнения факториалами 2Д массива
void setArrayFactorials(int** arr, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++) {
            int fact = 1;
            for (int k = 1; k <= i + j; k++)
                fact *= k;
            arr[i][j] = fact;
        }
}

//Создание 2Д массива
int** create2DArray(size_t ROWS, size_t COLS) {
    int** array2D = new int* [ROWS];

    for (size_t i = 0; i < ROWS; i++) {
        array2D[i] = new int[COLS];
    }

    return array2D;
}

//Форматирование до 8 позиций
string formatToWidth(int value, int width = 8) {
    string result = to_string(value);

    if (result.length() < width) {
        string spaces(width - result.length(), ' ');
        result = spaces + result;  // пробелы спереди
    }

    return result;
}

// Функция вывода 2D массива
void printArray(int** arr, size_t rows, size_t cols) {

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << formatToWidth(arr[i][j]) << "\t";
        }
        cout << endl;
    }
}

size_t getOddCount(size_t rows) {
    size_t oddRowsCount = 0;
    for (size_t i = 1; i <= rows; i++) {
        if (i % 2 != 0) {  // если нечётная (1, 3)
            oddRowsCount++;
        }
    }
    return oddRowsCount;
}

//Заполняем одномерный массив элементами из нечётных строк
void set1DArrByOddRows2DArr(int* oneDArray,int** array2D, size_t rows, size_t cols) {
    size_t index = 0;  // индекс в одномерном массиве

    for (size_t i = 0; i < rows; i++) {
        size_t realRowCount = i + 1; //Смещение нумерации строк на обычный манер по которому строилась задача
        if (realRowCount % 2 != 0) {  // если строка нечётная
            for (size_t j = 0; j < cols; j++) {
                oneDArray[index] = array2D[i][j];
                index++;
            }
        }
    }
}

void print1DArray(int* arr, size_t size) {
    cout << "[ ";
    for (size_t i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]";
    cout << endl;
}

// Функция удаления двумерного массива
void delete2DArray(int** arr, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

void task2() {
    const size_t ROWS = 5;
    const size_t COLS = 5;

    //Создаём двумерный массив
    int** twoDArray = create2DArray(ROWS, COLS);

    setArrayFactorials(twoDArray, ROWS, COLS);
    printArray(twoDArray, ROWS, COLS);

    //Вычислим размер одномерного массива
    size_t oneDArraySize = getOddCount(ROWS) * COLS;
    //Создаём одномерный массив
    int* oneDArray = new int[oneDArraySize];

    set1DArrByOddRows2DArr(oneDArray, twoDArray, ROWS, COLS);
    print1DArray(oneDArray, oneDArraySize);

    delete[] oneDArray;
    delete2DArray(twoDArray, ROWS);

}