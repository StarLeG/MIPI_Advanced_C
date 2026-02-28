#ifndef PLOTTING_H
#define PLOTTING_H

// Функция для построения графиков с использованием gnuplot
void plot_graphs(double eps1, double eps2);

// Вспомогательные функции для генерации данных
void generate_plot_data(double x1, double x2, double x3, double eps2);
void save_intersection_points(double x1, double x2, double x3);

#endif // PLOTTING_H