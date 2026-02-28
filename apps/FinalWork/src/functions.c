#include "functions.h"
#include <math.h>
#include <stdio.h>

// Функции
double f1(double x) {
    return 0.6 * x + 3;
}

double f2(double x) {
    return pow(x - 2, 3) - 1;
}

double f3(double x) {
    if (fabs(x) < 1e-10) return 1e10; // Избегаем деления на ноль
    return 3.0 / x;
}

// Производные
double f1_derivative(double x) {
    (void)x; // Подавляем предупреждение о неиспользуемом параметре
    return 0.6;
}

double f2_derivative(double x) {
    return 3 * pow(x - 2, 2);
}

double f3_derivative(double x) {
    if (fabs(x) < 1e-10) return 0;
    return -3.0 / (x * x);
}

// Получение функции по индексу
func_ptr get_function(int index) {
    switch (index) {
        case 1: return f1;
        case 2: return f2;
        case 3: return f3;
        default: return NULL;
    }
}

func_ptr get_derivative(int index) {
    switch (index) {
        case 1: return f1_derivative;
        case 2: return f2_derivative;
        case 3: return f3_derivative;
        default: return NULL;
    }
}

const char* get_function_name(int index) {
    switch (index) {
        case 1: return "f1(x) = 0.6x + 3";
        case 2: return "f2(x) = (x-2)^3 - 1";
        case 3: return "f3(x) = 3/x";
        default: return "Неизвестная функция";
    }
}