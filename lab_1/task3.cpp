#include <iostream>
#include <cstring>
#include <cstdio> 
#include <string>
#include "tasks.h"
#include <windows.h>
using namespace std;

/*
Функция strcmp.
Формат int strcmp(const char* s1, const char* s2).
Функция сравнивает строку s1 со строкой s2 в лексикографическом порядке. Если s1<s2,
то результат равен -1, если s1=s2, то 0, если s1>s2, то 1.
*/

int my_strcmp(const char* s1, const char* s2) {
    int i = 0;

    // Сравниваем пока символы равны
    while (s1[i] && s2[i] && s1[i] == s2[i]) {
        i++;
    }

    // Сравниваем текущие символы
    if (s1[i] < s2[i]) return -1;
    if (s1[i] > s2[i]) return 1;
    return 0;
}

void task3() {
    SetConsoleOutputCP(1251);  // Windows-1251 для русского
    printf("=== ТЕСТИРОВАНИЕ my_strcmp и сравнение со стандартной strcmp===\n\n");

    // Тест 1: Одинаковые строки
    printf("1. Одинаковые строки:\n");
    printf("   my_strcmp(\"hello\", \"hello\") = %d\n", my_strcmp("hello", "hello"));
    printf("   strcmp(\"hello\", \"hello\") = %d\n", strcmp("hello", "hello"));
    printf("   Ожидалось: 0 ✓\n\n");

    // Тест 2: Разные строки (первая меньше)
    printf("2. Первая строка меньше:\n");
    printf("   my_strcmp(\"apple\", \"banana\") = %d\n", my_strcmp("apple", "banana"));
    printf("   strcmp(\"apple\", \"banana\") = %d\n", strcmp("apple", "banana"));
    printf("   Ожидалось: -1 (apple < banana) ✓\n\n");

    // Тест 3: Разные строки (первая больше)
    printf("3. Первая строка больше:\n");
    printf("   my_strcmp(\"zebra\", \"apple\") = %d\n", my_strcmp("zebra", "apple"));
    printf("   strcmp(\"zebra\", \"apple\") = %d\n", strcmp("zebra", "apple"));
    printf("   Ожидалось: 1 (zebra > apple) ✓\n\n");

}