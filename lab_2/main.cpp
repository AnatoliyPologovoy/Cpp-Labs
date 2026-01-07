// main.cpp
#include <iostream>
#include "Vector.h"  // подключаем наш класс
#include <windows.h>
using namespace std;

// Функция для создания тестового 2D массива
int** createTestMatrix(size_t rows, size_t cols) {
    int** matrix = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = i * 10 + j;  // заполняем тестовыми значениями
        }
    }
    return matrix;
}

// Функция для удаления 2D массива
void deleteMatrix(int** matrix, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция для вывода 2D массива
void printMatrix(int** matrix, size_t rows, size_t cols) {
    cout << "Двумерный массив " << rows << "x" << cols << ":" << endl;
    for (size_t i = 0; i < rows; i++) {
        cout << "Строка " << i << ": [ ";
        for (size_t j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

int main() {
    SetConsoleOutputCP(1251);  // Windows-1251 для русского
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА Vector ===" << endl;
    cout << "=========================================" << endl << endl;

    // Тестовые данные
    const size_t ROWS = 5;
    const size_t COLS = 4;

    // 1. Создаём тестовый 2D массив
    cout << "1. Создаём двумерный массив " << ROWS << "x" << COLS << endl;
    int** matrix = createTestMatrix(ROWS, COLS);
    printMatrix(matrix, ROWS, COLS);

    cout << "\n2. Создаём Vector разными способами:" << endl;
    cout << "--------------------------------------" << endl;

    // 2.1 Создаём пустой вектор, потом заполняем из 2D массива
    cout << "\nа) Пустой вектор + setByOddRows2DArr:" << endl;
    Vector v1;
    cout << "   До заполнения: ";
    v1.print();

    v1.setByOddRows2DArr(matrix, ROWS, COLS);
    cout << "   После заполнения из нечётных строк: ";
    v1.print();

    // 2.2 Создаём вектор определённого размера
    cout << "\nб) Вектор заданного размера:" << endl;
    Vector v2(3);
    cout << "   Исходный вектор: ";
    v2.print();

    // Перезаполняем его из 2D массива
    v2.setByOddRows2DArr(matrix, ROWS, COLS);
    cout << "   После перезаполнения: ";
    v2.print();

    // 3. Тест с другим размером 2D массива
    cout << "\n3. Тест с другим двумерным массивом (3x3):" << endl;
    cout << "-------------------------------------------" << endl;

    // Создаём новый 2D массив
    int** smallMatrix = createTestMatrix(3, 3);
    printMatrix(smallMatrix, 3, 3);

    Vector v3;
    v3.setByOddRows2DArr(smallMatrix, 3, 3);
    cout << "Вектор из нечётных строк (1 и 3): ";
    v3.print();

    // 4. Проверка работы деструкторов
    cout << "\n4. Проверка деструкторов (выход из main):" << endl;
    cout << "-----------------------------------------" << endl;

    // Создадим ещё один вектор в блоке
    {
        cout << "   Создаём временный вектор в блоке..." << endl;
        Vector temp;
        temp.setByOddRows2DArr(matrix, 2, 2);
        cout << "   Временный вектор: ";
        temp.print();
        cout << "   Выход из блока - должен вызваться деструктор" << endl;
    }

    // 5. Очистка памяти
    cout << "\n5. Очистка памяти 2D массивов:" << endl;
    deleteMatrix(matrix, ROWS);
    deleteMatrix(smallMatrix, 3);

    cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;

    // Деструкторы v1, v2, v3 вызовутся автоматически при выходе из main

    return 0;
}