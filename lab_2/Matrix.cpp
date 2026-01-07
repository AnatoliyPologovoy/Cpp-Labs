#include <iostream>
#include <cstring>
#include <string>
#include "Matrix.h" 
using namespace std;

Matrix::Matrix() : data(nullptr), rows(0), cols(0) {
    cout << "Создан пустой 2D массив" << endl;
}

Matrix::Matrix(size_t r, size_t c) {
    rows = r;
    cols = c;
    data = new int*[r];
    for (size_t i = 0; i < r; i++) {
        data[i] = new int[c];
    }
    cout << "Создан 2D массив размером " << r << "x" << c << endl;

};

const int* const* Matrix::getData() const {
    return data;  // возвращаем как "только для чтения"
}

size_t Matrix::getRows() const {
    return rows;
};

size_t Matrix::getCols() const {
    return cols;
};

//Заполнение матрицы факториалами
void Matrix::setArrayFactorials() {
    if (data == nullptr) {
        return;
    };

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++) {
            int fact = 1;
            for (int k = 1; k <= i + j; k++)
                fact *= k;
            data[i][j] = fact;
        }
}

//Метод at() для получения значения (только чтение)
int Matrix::at(int i, int j) const {
    return data[i][j];
}

//Метод setAt() для установки значения
void Matrix::setAt(int i, int j, int val) {
    data[i][j] = val;
}

// ---------- ОПЕРАТОРЫ ИНКРЕМЕНТА И ДЕКРЕМЕНТА ----------

// 1. Префиксный инкремент (++matrix)
Matrix& Matrix::operator++() {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            ++data[i][j];
        }
    }
    return *this;
}

// 2. Постфиксный инкремент (matrix++)
Matrix Matrix::operator++(int) {
    Matrix temp(*this);  // Сохраняем текущее состояние
    ++(*this);           // Используем префиксный инкремент
    return temp;         // Возвращаем старое состояние
}

// 3. Префиксный декремент (--matrix)
Matrix& Matrix::operator--() {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            --data[i][j];
        }
    }
    return *this;
}

// 4. Постфиксный декремент (matrix--)
Matrix Matrix::operator--(int) {
    Matrix temp(*this);  // Сохраняем текущее состояние
    --(*this);           // Используем префиксный декремент
    return temp;         // Возвращаем старое состояние
}
// -------------------------------------------------------

//Форматирование чисел до нужной строковой ширины
string Matrix::formatToWidth(int value, int width) {
    string result = to_string(value);

    if (result.length() < width) {
        string spaces(width - result.length(), ' ');
        result = spaces + result;  // пробелы спереди
    }

    return result;
}


void Matrix::print() {
    cout << "[\n";
    for (size_t i = 0; i < rows; i++) {
        cout << "[";
        for (size_t j = 0; j < cols; j++) {
            cout << formatToWidth(data[i][j], 8) << "\t";
        }
        cout << "]";
        cout << endl;
    }
    cout << "]";
    cout << endl;
};

Matrix::~Matrix() {
    for (size_t i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
    cout << "Удалён 2D массив " << endl;
};
