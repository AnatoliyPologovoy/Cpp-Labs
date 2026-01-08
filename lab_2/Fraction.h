#pragma once
#ifndef FRACTION_H  // защита от повторного включения
#define FRACTION_H

#include <cstddef>  // для size_t
#include <string>  
using namespace std;

class Fraction {
private:
    int numerator;    // числитель
    int denominator;  // знаменатель

    // для сокращения дроби
    void reduce();

    // Нахождение наибольшего общего делителя
    static int gcd(int a, int b);

    // Статический счетчик экземпляров
    static int instanceCount;

public:
    // Конструкторы
    Fraction();                          // по умолчанию: 0/1
    Fraction(int num);                   // целое число: num/1
    Fraction(int num, int den);          // дробь: num/den

    // Геттеры
    int getNumerator() const;
    int getDenominator() const;

    // Сеттеры
    void setNumerator(int num);
    void setDenominator(int den);
    void set(int num, int den);          // установить и числитель, и знаменатель

    // Преобразования
    double toDouble() const;             // преобразование в double
    string toString() const;        // преобразование в строку

    // Вывод на экран
    void print() const;
    void printAsDouble() const;

    // Базовые операции
    Fraction add(const Fraction& other) const;
    Fraction subtract(const Fraction& other) const;
    Fraction multiply(const Fraction& other) const;
    Fraction divide(const Fraction& other) const;

    // ---------- ПЕРЕГРУЗКА ОПЕРАТОРОВ ----------

    // Унарные операторы
    Fraction operator+() const;          // унарный плюс
    Fraction operator-() const;          // унарный минус

    // Бинарные арифметические операторы
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Составные операторы присваивания
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);

    // -------------------------------------------

    // Преобразование десятичной дроби в строку с обыкновенной дробью
    static string decimalStringToFraction(const string& decimalStr);

    // Вывод десятичной дроби в виде обыкновенной
    static void printAsFraction(double decimal_fraction);
    static void printAsFraction(const char* decimal_fraction);

    // Статический метод для получения количества созданных экземпляров
    static int getInstanceCount();

    ~Fraction();
};

void demonstrateFractionClass();

#endif // FRACTION_H