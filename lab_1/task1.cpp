#include <iostream>
#include <cstring>
#include <string>
#include "tasks.h"

//¬ариант 2. «адание 1.
//ќбъ€вить массив из n = 20 вещественных чисел, проинициализировать нул€ми.‘ункци€
//processArray() должна заполнить массив случайными числами от - 20.0 до 70.0, а
//затем отнормировать массив, т.е.поделить каждый элемент массива на максимальное
//по модулю значение в массиве.Ёто значение она также должна вернуть на выходе.
//—формировать выходной вещественный массив, в котором все элементы, сто€щие до
//позиции максимального элемента включительно, повтор€ют элементы входного
//массива, а остальные равны x(число x ввести с клавиатуры).¬ывести на экран
//результирующие массивы.

double processArray(double arr[], size_t n) {
	// заполнение массива случ. числами 
	for (size_t i = 0; i < n; ++i)
	{
		arr[i] = (double)(rand() % 91) - 20; //случ. число в диапазоне  -20.0 до 70.0
	}

	double max = 0.0;
	// поиск максимального значени€ по модулю
	for (size_t i = 0; i < n; ++i)
	{
		if (fabs(arr[i]) > max) {
			max = fabs(arr[i]);
		}
	}

	//нормализаци€ массива
	for (size_t i = 0; i < n; ++i)
	{
		arr[i] /= max;
	}

	return max;
};


void printArray(double arr[], size_t n) {
	std::string result = "[ ";

	for (size_t i = 0; i < n; ++i)
	{
		result += std::to_string(arr[i]);
		result += " ";
	}
	result += " ]";
	std::cout << result << std::endl;
}

//—формировать выходной вещественный массив, в котором все элементы, сто€щие до 
//позиции максимального элемента включительно, повтор€ют элементы входного
//массива, а остальные равны x.
void replaceItemsArray(double arr[], size_t n, double x) {
	bool isReplace = false;
	const int NORMALIZE_MAX_COEFF = 1; // максимальный элемент дл€ нормализованного массива
	for (size_t i = 0; i < n; ++i)
	{
		if (isReplace) {
			arr[i] = x;
		}
		else if (arr[i] == double(NORMALIZE_MAX_COEFF)) { 
			isReplace = true;
		}
	}

};

void task1() {
	// размер массива равен 20 (по заданию) 
	const size_t N = 20;

	double a[N] = { 0.0 }; // создаем массив и инициализируем нул€ми 
	double input;

	// инициализаци€ генератора случайных чисел 
	srand(0);

	// поиск максимального значени€ в массиве а, изменение массива a 
	double max = processArray(a, N);
	// вывод на экран 
	printf("max Item = %g\n\n", max);
	printArray(a, N);

	std::cout << "¬ведите число: ";
	std::cin >> input;

	replaceItemsArray(a, N, input);
	printArray(a, N);

}