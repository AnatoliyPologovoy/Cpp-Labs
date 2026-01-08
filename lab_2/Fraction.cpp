#include "Fraction.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <limits>

using namespace std;

int Fraction::instanceCount = 0;

// Статический метод для получения счетчика
int Fraction::getInstanceCount() {
    return instanceCount;
}

// Нахождение НОД алгоритмом Евклида
int Fraction::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Сокращение дроби
void Fraction::reduce() {
    if (denominator == 0) {
        throw runtime_error("Denominator cannot be zero");
    }

    // Знак храним в числителе
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    // Сокращаем на НОД
    int divisor = gcd(numerator, denominator);
    if (divisor > 1) {
        numerator /= divisor;
        denominator /= divisor;
    }

    // Если числитель 0, знаменатель делаем 1
    if (numerator == 0) {
        denominator = 1;
    }
}

// Конструкторы
Fraction::Fraction() : numerator(0), denominator(1) {
    instanceCount++;
}

Fraction::Fraction(int num) : numerator(num), denominator(1) {
    instanceCount++;
}

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    if (den == 0) {
        throw invalid_argument("Denominator cannot be zero");
    }
    reduce();
    instanceCount++;
}

// Геттеры
int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

// Сеттеры
void Fraction::setNumerator(int num) {
    numerator = num;
    reduce();
}

void Fraction::setDenominator(int den) {
    if (den == 0) {
        throw invalid_argument("Denominator cannot be zero");
    }
    denominator = den;
    reduce();
}

void Fraction::set(int num, int den) {
    if (den == 0) {
        throw invalid_argument("Denominator cannot be zero");
    }
    numerator = num;
    denominator = den;
    reduce();
}

// Деструктор - уменьшает счетчик
Fraction::~Fraction() {
    instanceCount--;
}

// Преобразования
double Fraction::toDouble() const {
    if (denominator == 0) {
        throw runtime_error("Division by zero");
    }
    return static_cast<double>(numerator) / denominator;
}

string Fraction::toString() const {
    stringstream ss;
    if (denominator == 1) {
        ss << numerator;
    }
    else {
        ss << numerator << "/" << denominator;
    }
    return ss.str();
}

// Вывод на экран
void Fraction::print() const {
    cout << toString();
}

void Fraction::printAsDouble() const {
    cout << toDouble();
}

// Базовые операции
Fraction Fraction::add(const Fraction& other) const {
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::subtract(const Fraction& other) const {
    int num = numerator * other.denominator - other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::multiply(const Fraction& other) const {
    int num = numerator * other.numerator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::divide(const Fraction& other) const {
    if (other.numerator == 0) {
        throw invalid_argument("Division by zero fraction");
    }
    int num = numerator * other.denominator;
    int den = denominator * other.numerator;
    return Fraction(num, den);
}

// ---------- ПЕРЕГРУЗКА ОПЕРАТОРОВ ----------

// Унарные операторы
Fraction Fraction::operator+() const {
    return *this;  // Просто возвращаем копию объекта
}

Fraction Fraction::operator-() const {
    return Fraction(-numerator, denominator);  // Меняем знак числителя
}

// Бинарные арифметические операторы
Fraction Fraction::operator+(const Fraction& other) const {
    // a/b + c/d = (a*d + c*b) / (b*d)
    int num = numerator * other.denominator + other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::operator-(const Fraction& other) const {
    // a/b - c/d = (a*d - c*b) / (b*d)
    int num = numerator * other.denominator - other.numerator * denominator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::operator*(const Fraction& other) const {
    // (a/b) * (c/d) = (a*c) / (b*d)
    int num = numerator * other.numerator;
    int den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::operator/(const Fraction& other) const {
    // (a/b) / (c/d) = (a*d) / (b*c)
    if (other.numerator == 0) {
        throw invalid_argument("Division by zero fraction");
    }
    int num = numerator * other.denominator;
    int den = denominator * other.numerator;
    return Fraction(num, den);
}

// Составные операторы присваивания
Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

 //Преобразование десятичной дроби в строку с обыкновенной дробью
string Fraction::decimalStringToFraction(const string& decimalStr) {
    string str = decimalStr;

    // Убираем пробелы
    while (!str.empty() && str[0] == ' ') str.erase(0, 1);
    while (!str.empty() && str.back() == ' ') str.pop_back();

    if (str.empty()) return "0";

    // Знак
    bool negative = false;
    if (str[0] == '-') {
        negative = true;
        str = str.substr(1);
    }
    else if (str[0] == '+') {
        str = str.substr(1);
    }

    // Находим разделитель
    size_t dot = str.find('.');
    if (dot == string::npos) dot = str.find(',');

    if (dot == string::npos) {
        // Целое число
        for (char c : str) {
            if (!isdigit(c)) return "0";
        }

        int num = 0;
        for (char c : str) {
            num = num * 10 + (c - '0');
        }
        if (negative) num = -num;
        return to_string(num);
    }

    // Целая часть
    string intPart = str.substr(0, dot);
    string fracPart = str.substr(dot + 1);

    // Проверяем цифры
    for (char c : intPart) {
        if (!isdigit(c)) return "0";
    }
    for (char c : fracPart) {
        if (!isdigit(c)) return "0";
    }

    // Конвертируем
    int intVal = 0;
    for (char c : intPart) {
        intVal = intVal * 10 + (c - '0');
    }

    int fracVal = 0;
    for (char c : fracPart) {
        fracVal = fracVal * 10 + (c - '0');
    }

    // Знаменатель
    int denominator = 1;
    for (size_t i = 0; i < fracPart.length(); i++) {
        denominator *= 10;
    }

    // Общий числитель
    int numerator = intVal * denominator + fracVal;
    if (negative) numerator = -numerator;

    // Сокращаем
    int a = abs(numerator);
    int b = denominator;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    if (a > 1) {
        numerator /= a;
        denominator /= a;
    }

    if (numerator == 0) return "0";
    if (denominator == 1) return to_string(numerator);
    return to_string(numerator) + "/" + to_string(denominator);
}

// Вывод десятичной дроби в виде обыкновенной (из double)
void Fraction::printAsFraction(double decimal_fraction) {

    // Используем строковое представление для точности
    stringstream ss;
    ss.precision(15);  // Высокая точность
    ss << fixed << decimal_fraction;

    // Преобразуем строку в дробь
    cout << decimalStringToFraction(ss.str());

}

// Вывод десятичной дроби в виде обыкновенной (из строки C-style)
void Fraction::printAsFraction(const char* decimal_fraction) {
    if (decimal_fraction == nullptr) {
        cout << "Error: null pointer";
        return;
    }

    cout << decimalStringToFraction(decimal_fraction);
}

void demonstrateFractionClass() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА Fraction ===\n\n";

    // Показать начальный счетчик экземпляров
    cout << "1. Начальный счетчик экземпляров: "
        << Fraction::getInstanceCount() << "\n\n";

    // Создание дробей
    cout << "2. Создание объектов дробей:\n";
    Fraction f1;                    // 0/1
    Fraction f2(3);                 // 3/1
    Fraction f3(1, 2);              // 1/2
    Fraction f4(2, 4);              // 2/4 = 1/2 после сокращения
    Fraction f5(-3, 4);             // -3/4
    Fraction f6(4, -2);             // 4/-2 = -2/1

    cout << "   f1 = " << f1.toString() << endl;
    cout << "   f2 = " << f2.toString() << endl;
    cout << "   f3 = " << f3.toString() << endl;
    cout << "   f4 = " << f4.toString() << " (автоматическое сокращение)" << endl;
    cout << "   f5 = " << f5.toString() << endl;
    cout << "   f6 = " << f6.toString() << " (нормализация знака)" << endl;

    cout << "\n   Счетчик после создания 6 дробей: "
        << Fraction::getInstanceCount() << "\n\n";

    // Арифметические операции с использованием методов
    cout << "3. Арифметические операции (через методы):\n";

    Fraction sum = f3.add(f4);      // 1/2 + 1/2
    Fraction diff = f3.subtract(f5); // 1/2 - (-3/4)
    Fraction prod = f3.multiply(f5); // 1/2 * (-3/4)
    Fraction quot = f3.divide(f4);  // 1/2 ÷ 1/2

    cout << "   f3 + f4 = " << f3.toString() << " + " << f4.toString()
        << " = " << sum.toString() << endl;
    cout << "   f3 - f5 = " << f3.toString() << " - " << f5.toString()
        << " = " << diff.toString() << endl;
    cout << "   f3 * f5 = " << f3.toString() << " * " << f5.toString()
        << " = " << prod.toString() << endl;
    cout << "   f3 / f4 = " << f3.toString() << " / " << f4.toString()
        << " = " << quot.toString() << endl;

    // Арифметические операции с использованием перегруженных операторов
    cout << "\n4. Арифметические операции (через операторы):\n";

    Fraction a(1, 3);
    Fraction b(1, 6);
    Fraction c(2, 3);

    cout << "   a = " << a.toString() << ", b = " << b.toString()
        << ", c = " << c.toString() << endl;

    Fraction result1 = a + b;
    Fraction result2 = a - b;
    Fraction result3 = a * b;
    Fraction result4 = a / b;

    cout << "   a + b = " << result1.toString() << endl;
    cout << "   a - b = " << result2.toString() << endl;
    cout << "   a * b = " << result3.toString() << endl;
    cout << "   a / b = " << result4.toString() << endl;

    // Составные операторы
    cout << "\n5. Составные операторы:\n";

    Fraction x(1, 2);
    Fraction y(1, 3);

    cout << "   Начальное x = " << x.toString() << endl;

    x += y;
    cout << "   После x += y: x = " << x.toString() << endl;

    x -= Fraction(1, 6);
    cout << "   После x -= 1/6: x = " << x.toString() << endl;

    x *= Fraction(3, 2);
    cout << "   После x *= 3/2: x = " << x.toString() << endl;

    x /= Fraction(2, 1);
    cout << "   После x /= 2: x = " << x.toString() << endl;

    // Унарные операторы
    cout << "\n6. Унарные операторы:\n";

    Fraction pos(3, 4);
    Fraction neg = -pos;

    cout << "   +" << pos.toString() << " = " << (+pos).toString() << endl;
    cout << "   -" << pos.toString() << " = " << neg.toString() << endl;

    // Статические методы для преобразования десятичных дробей
    cout << "\n7. Статические методы преобразования десятичных дробей:\n";

    cout << "   printAsFraction(0.43): ";
    Fraction::printAsFraction(0.43);
    cout << endl;

    cout << "   printAsFraction(0.25): ";
    Fraction::printAsFraction(0.25);
    cout << endl;

    cout << "   printAsFraction(1.5): ";
    Fraction::printAsFraction(1.5);
    cout << endl;

    cout << "   printAsFraction(\"0.125\"): ";
    Fraction::printAsFraction("0.125");
    cout << endl;

    cout << "   printAsFraction(\"0.333\"): ";
    Fraction::printAsFraction("0.333");
    cout << endl;

    // Метод decimalStringToFraction (возвращает строку)
    cout << "\n8. Метод decimalStringToFraction (возвращает строку):\n";

    string frac1 = Fraction::decimalStringToFraction("0.75");
    string frac2 = Fraction::decimalStringToFraction("0.2");
    string frac3 = Fraction::decimalStringToFraction("1.25");

    cout << "   0.75 = " << frac1 << endl;
    cout << "   0.2 = " << frac2 << endl;
    cout << "   1.25 = " << frac3 << endl;

    // Демонстрация счетчика экземпляров с временными объектами
    cout << "\n9. Демонстрация счетчика с временными объектами:\n";

    int initialCount = Fraction::getInstanceCount();
    cout << "   Текущий счетчик: " << initialCount << endl;

    {
        Fraction temp1(1, 5);
        Fraction temp2(2, 7);
        cout << "   Счетчик внутри блока: " << Fraction::getInstanceCount() << endl;
    } // temp1 и temp2 уничтожаются здесь

    cout << "   Счетчик после блока: " << Fraction::getInstanceCount() << endl;

    // Дополнительные операции
    cout << "\n10. Дополнительные операции и преобразования:\n";

    Fraction complex(5, 8);
    cout << "   Дробь: " << complex.toString() << endl;
    cout << "   В десятичном виде: " << complex.toDouble() << endl;
    cout << "   Через print(): ";
    complex.print();
    cout << endl;
    cout << "   Через printAsDouble(): ";
    complex.printAsDouble();
    cout << endl;

    // Сеттеры и геттеры
    cout << "\n11. Работа сеттеров и геттеров:\n";

    Fraction f;
    f.set(3, 9);
    cout << "   После set(3, 9): " << f.toString() << " (сократилось до 1/3)" << endl;

    f.setNumerator(4);
    cout << "   После setNumerator(4): " << f.toString() << endl;

    f.setDenominator(12);
    cout << "   После setDenominator(12): " << f.toString() << " (сократилось до 1/3)" << endl;

    cout << "   Числитель: " << f.getNumerator() << endl;
    cout << "   Знаменатель: " << f.getDenominator() << endl;

    // Итоговый счетчик
    cout << "\n12. Итоговый счетчик экземпляров: "
        << Fraction::getInstanceCount() << endl;

    cout << "\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n";
}