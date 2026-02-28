/**
 * @file plotting.h
 * @brief Модуль для визуализации графиков функций
 * 
 * Генерирует данные и создаёт скрипт для построения графиков в gnuplot
 */

#ifndef PLOTTING_H
#define PLOTTING_H

/**
 * @brief Построение графиков функций с использованием gnuplot
 * 
 * Находит точки пересечения, генерирует данные, создаёт скрипт gnuplot
 * и запускает его для визуализации.
 * 
 * @param eps1 Точность для поиска корней
 * @param eps2 Точность для интегрирования
 */
void plot_graphs(double eps1, double eps2);

/**
 * @brief Генерация данных для построения графиков
 * 
 * Создаёт файлы с точками для каждой функции в заданном диапазоне.
 * 
 * @param x1 Точка пересечения f1 и f3
 * @param x2 Точка пересечения f2 и f3
 * @param x3 Точка пересечения f1 и f2
 * @param eps2 Точность интегрирования (для информации)
 */
void generate_plot_data(double x1, double x2, double x3, double eps2);

/**
 * @brief Сохранение точек пересечения в файл
 * 
 * Создаёт файл intersections.txt с координатами точек пересечения
 * и значениями всех трёх функций в этих точках.
 * 
 * @param x1 Точка пересечения f1 и f3
 * @param x2 Точка пересечения f2 и f3
 * @param x3 Точка пересечения f1 и f2
 */
void save_intersection_points(double x1, double x2, double x3);

#endif // PLOTTING_H