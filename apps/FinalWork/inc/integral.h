#ifndef INTEGRAL_H
#define INTEGRAL_H

#include "functions.h"

// Структура для хранения результата интегрирования
typedef struct {
    double result;      // вычисленное значение интеграла
    int iterations;     // количество итераций (разбиений)
    int success;        // флаг успеха (1 - успешно, 0 - ошибка)
} IntegralResult;

// Функция численного интегрирования адаптивным методом Симпсона
// Параметры:
//   f - указатель на интегрируемую функцию
//   a, b - пределы интегрирования [a, b]
//   eps2 - требуемая точность вычисления интеграла
IntegralResult integral(func_ptr f, double a, double b, double eps2);

// Тестовая функция для проверки интегрирования
void test_integral(void);

#endif // INTEGRAL_H