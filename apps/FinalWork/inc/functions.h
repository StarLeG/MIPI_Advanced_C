/**
 * @file functions.h
 * @brief Заголовочный файл с определением математических функций
 * 
 * Содержит три функции f1, f2, f3 и их производные,
 * а также вспомогательные функции для работы с ними по индексу
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @brief Тип указателя на математическую функцию
 */
typedef double (*func_ptr)(double);

/**
 * @brief Линейная функция f1(x) = 0.6x + 3
 * @param x Аргумент функции
 * @return Значение функции
 */
double f1(double x);

/**
 * @brief Кубическая функция f2(x) = (x-2)^3 - 1
 * @param x Аргумент функции
 * @return Значение функции
 */
double f2(double x);

/**
 * @brief Гиперболическая функция f3(x) = 3/x
 * @param x Аргумент функции (x > 0)
 * @return Значение функции
 */
double f3(double x);

/**
 * @brief Производная f1: f1'(x) = 0.6
 * @param x Аргумент функции
 * @return Значение производной
 */
double f1_derivative(double x);

/**
 * @brief Производная f2: f2'(x) = 3(x-2)^2
 * @param x Аргумент функции
 * @return Значение производной
 */
double f2_derivative(double x);

/**
 * @brief Производная f3: f3'(x) = -3/x^2
 * @param x Аргумент функции (x > 0)
 * @return Значение производной
 */
double f3_derivative(double x);

/**
 * @brief Получить функцию по её индексу
 * @param index Номер функции (1, 2 или 3)
 * @return Указатель на функцию или NULL если индекс неверный
 */
func_ptr get_function(int index);

/**
 * @brief Получить производную функции по её индексу
 * @param index Номер функции (1, 2 или 3)
 * @return Указатель на функцию производной или NULL если индекс неверный
 */
func_ptr get_derivative(int index);

/**
 * @brief Получить строку с именем функции
 * @param index Номер функции (1, 2 или 3)
 * @return Строка с описанием функции
 */
const char* get_function_name(int index);

#endif // FUNCTIONS_H