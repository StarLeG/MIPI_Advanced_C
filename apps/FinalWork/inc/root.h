#ifndef ROOT_H
#define ROOT_H

#include "functions.h"

// Структура для хранения результата поиска корня
typedef struct {
    double root;        // найденный корень
    int iterations;     // количество итераций
    int success;        // флаг успеха (1 - успешно, 0 - ошибка)
} RootResult;

// Функция поиска корня комбинированным методом (секущих + бисекции)
// Параметры:
//   f, g - указатели на функции (f(x) = g(x))
//   a, b - интервал поиска [a, b]
//   eps1 - точность по x
RootResult root(func_ptr f, func_ptr g, double a, double b, double eps1);

// Тестовая функция для проверки поиска корня
void test_root(void);

#endif // ROOT_H