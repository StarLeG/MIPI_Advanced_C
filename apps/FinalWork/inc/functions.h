#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Типы функций
typedef double (*func_ptr)(double);

// Наши три функции
double f1(double x);
double f2(double x);
double f3(double x);

// Производные
double f1_derivative(double x);
double f2_derivative(double x);
double f3_derivative(double x);

// Функция для получения функции по индексу
func_ptr get_function(int index);
func_ptr get_derivative(int index);

// Функция для получения имени функции
const char* get_function_name(int index);

#endif // FUNCTIONS_H