#ifndef VECTOR_H  // защита от повторного включения
#define VECTOR_H

#include <cstddef>  // для size_t

class Vector {
private:
    int* data;      // указатель на массив чисел
    size_t size;    // размер вектора

public:
    // Конструкторы
    Vector();
    Vector(size_t s);
    int& operator[](size_t index);
    // Метод для заполнения из нечетных строк 2D массива
    void setByOddRows2DArr(const int* const* array2D, size_t rows, size_t cols);

    // Метод для вывода
    void print();

    // Деструктор
    ~Vector();
};

#endif // VECTOR_H