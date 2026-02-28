#include "plotting.h"
#include "functions.h"
#include "root.h"
#include "integral.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void save_intersection_points(double x1, double x2, double x3) {
    FILE *fp = fopen("intersections.txt", "w");
    if (fp == NULL) {
        printf("Ошибка: не удалось создать файл intersections.txt\n");
        return;
    }
    
    fprintf(fp, "# Точки пересечения функций\n");
    fprintf(fp, "# Для каждой точки показаны значения ВСЕХ трёх функций\n");
    fprintf(fp, "# x\tf1(x)\tf2(x)\tf3(x)\tописание\n");
    fprintf(fp, "%.10f\t%.10f\t%.10f\t%.10f\t# f1=f3 (x1)\n", x1, f1(x1), f2(x1), f3(x1));
    fprintf(fp, "%.10f\t%.10f\t%.10f\t%.10f\t# f2=f3 (x2)\n", x2, f1(x2), f2(x2), f3(x2));
    fprintf(fp, "%.10f\t%.10f\t%.10f\t%.10f\t# f1=f2 (x3)\n", x3, f1(x3), f2(x3), f3(x3));
    
    fclose(fp);
    printf("Сохранены точки пересечения в файл intersections.txt\n");
}

void generate_plot_data(double x1, double x2, double x3, double eps2) {
    (void)eps2; // Подавляем предупреждение о неиспользуемом параметре
    
    // Определяем диапазон для графика
    double x_min = 0.0;
    double x_max = x3 + 1.5;
    
    int num_points = 2000;
    double step = (x_max - x_min) / num_points;
    
    // Создаем файлы с данными
    FILE *fp1 = fopen("f1_data.txt", "w");
    FILE *fp2 = fopen("f2_data.txt", "w");
    FILE *fp3 = fopen("f3_data.txt", "w");
    FILE *fp_points = fopen("points_data.txt", "w");
    
    if (!fp1 || !fp2 || !fp3 || !fp_points) {
        printf("Ошибка: не удалось создать файлы данных\n");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        if (fp3) fclose(fp3);
        if (fp_points) fclose(fp_points);
        return;
    }
    
    // Заголовки файлов
    fprintf(fp1, "# x\tf1(x)\n");
    fprintf(fp2, "# x\tf2(x)\n");
    fprintf(fp3, "# x\tf3(x)\n");
    fprintf(fp_points, "# x\ty\ttype\n");
    
    // Сохраняем точки пересечения с правильными значениями y
    fprintf(fp_points, "%.10f\t%.10f\t1  # x1 (f1=f3) y = %.6f\n", x1, f1(x1), f1(x1));
    fprintf(fp_points, "%.10f\t%.10f\t2  # x2 (f2=f3) y = %.6f\n", x2, f2(x2), f2(x2));
    fprintf(fp_points, "%.10f\t%.10f\t3  # x3 (f1=f2) y = %.6f\n", x3, f1(x3), f1(x3));
    
    // Генерируем точки для графиков
    for (int i = 0; i <= num_points; i++) {
        double x = x_min + i * step;
        
        // Данные для функций
        fprintf(fp1, "%.10f\t%.10f\n", x, f1(x));
        fprintf(fp2, "%.10f\t%.10f\n", x, f2(x));
        
        // Для f3 пропускаем x <= 0 (где функция не определена)
        if (x > 0.01) {
            fprintf(fp3, "%.10f\t%.10f\n", x, f3(x));
        }
    }
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp_points);
    
    printf("Сгенерированы данные для графиков:\n");
    printf("  f1_data.txt - данные для f1(x) (линейная функция)\n");
    printf("  f2_data.txt - данные для f2(x) = (x-2)^3 - 1\n");
    printf("  f3_data.txt - данные для f3(x) = 3/x\n");
    printf("  points_data.txt - точки пересечения с правильными значениями y\n");
}

void plot_graphs(double eps1, double eps2) {
    printf("Построение графиков функций...\n");
    printf("==============================\n");
    
    // Находим точки пересечения с правильными интервалами
    printf("Поиск точек пересечения с точностью eps1 = %e...\n", eps1);
    
    RootResult r13 = root(f1, f3, 0.1, 5, eps1);  // f1=f3 около 0.85
    RootResult r23 = root(f2, f3, 0.1, 5, eps1);  // f2=f3 около 3.24
    RootResult r12 = root(f1, f2, 3, 4, eps1);    // f1=f2 правый корень около 3.85
    
    // Проверка успешности
    int success_count = 0;
    if (r13.success) success_count++;
    if (r23.success) success_count++;
    if (r12.success) success_count++;
    
    if (success_count < 3) {
        printf("Ошибка: не удалось найти все точки пересечения\n");
        printf("  f1=f3: %s (x = %f, итераций: %d)\n", 
               r13.success ? "успех" : "неудача", r13.root, r13.iterations);
        printf("  f2=f3: %s (x = %f, итераций: %d)\n", 
               r23.success ? "успех" : "неудача", r23.root, r23.iterations);
        printf("  f1=f2: %s (x = %f, итераций: %d)\n", 
               r12.success ? "успех" : "неудача", r12.root, r12.iterations);
        
        // Используем известные приближения в случае ошибки
        if (!r13.success) r13.root = 0.854109;
        if (!r23.success) r23.root = 3.243927;
        if (!r12.success) r12.root = 3.847753;
        printf("\nИспользую известные приближения для построения графиков.\n");
    }
    
    // Точки должны быть в порядке возрастания: x1 (f1=f3) < x2 (f2=f3) < x3 (f1=f2)
    double x1 = r13.root;  // ~0.85
    double x2 = r23.root;  // ~3.24  
    double x3 = r12.root;  // ~3.85
    
    printf("\nНайденные точки пересечения:\n");
    printf("  x1 (f1 = f3) = %.10f\n", x1);
    printf("    f1(x1) = %f, f3(x1) = %f, разность = %e\n", 
           f1(x1), f3(x1), fabs(f1(x1) - f3(x1)));
    printf("  x2 (f2 = f3) = %.10f\n", x2);
    printf("    f2(x2) = %f, f3(x2) = %f, разность = %e\n", 
           f2(x2), f3(x2), fabs(f2(x2) - f3(x2)));
    printf("  x3 (f1 = f2) = %.10f\n", x3);
    printf("    f1(x3) = %f, f2(x3) = %f, разность = %e\n", 
           f1(x3), f2(x3), fabs(f1(x3) - f2(x3)));
    
    // Сохраняем точки пересечения
    save_intersection_points(x1, x2, x3);
    
    // Генерируем данные для графиков
    generate_plot_data(x1, x2, x3, eps2);
    
    // Вычисляем площадь для отображения на графике
    IntegralResult int_f1_1 = integral(f1, x1, x2, eps2);
    IntegralResult int_f2_1 = integral(f2, x1, x2, eps2);
    IntegralResult int_f2_2 = integral(f2, x2, x3, eps2);
    IntegralResult int_f3_2 = integral(f3, x2, x3, eps2);
    double area = (int_f1_1.result - int_f2_1.result) + (int_f2_2.result - int_f3_2.result);
    
    // Создаем скрипт для gnuplot
    FILE *gp_script = fopen("plot_script.gp", "w");
    if (!gp_script) {
        printf("Ошибка: не удалось создать скрипт gnuplot\n");
        return;
    }
    
    fprintf(gp_script, "# Скрипт для gnuplot\n");
    fprintf(gp_script, "# Сгенерирован программой AreaCalculation\n\n");
    
    fprintf(gp_script, "set terminal pngcairo size 1400,1000 enhanced font 'Arial,14'\n");
    fprintf(gp_script, "set output 'functions_plot.png'\n");
    fprintf(gp_script, "set title 'Графики функций f1(x), f2(x) и f3(x)'\n");
    fprintf(gp_script, "set xlabel 'x'\n");
    fprintf(gp_script, "set ylabel 'y'\n");
    fprintf(gp_script, "set grid\n");
    fprintf(gp_script, "set key outside right\n");
    fprintf(gp_script, "set samples 2000\n\n");
    
    // Устанавливаем диапазоны
    fprintf(gp_script, "# Диапазоны для графика\n");
    fprintf(gp_script, "x_min = 0.0\n");
    fprintf(gp_script, "x_max = %f\n", x3 + 1.0);
    fprintf(gp_script, "set xrange [x_min:x_max]\n");
    fprintf(gp_script, "set yrange [-8:12]\n\n");
    
    // Добавляем вертикальные линии в точках пересечения
    fprintf(gp_script, "# Вертикальные линии в точках пересечения\n");
    fprintf(gp_script, "set arrow from %f, graph 0 to %f, graph 1 nohead lt 2 lc rgb 'gray' lw 1 dt 2\n", 
            x1, x1);
    fprintf(gp_script, "set arrow from %f, graph 0 to %f, graph 1 nohead lt 2 lc rgb 'gray' lw 1 dt 2\n", 
            x2, x2);
    fprintf(gp_script, "set arrow from %f, graph 0 to %f, graph 1 nohead lt 2 lc rgb 'gray' lw 1 dt 2\n\n", 
            x3, x3);
    
    // Добавляем метки для точек пересечения
    fprintf(gp_script, "# Метки для точек пересечения\n");
    fprintf(gp_script, "set label 'x1 (f1=f3)' at %f, 4.5 center front textcolor rgb 'red'\n", x1);
    fprintf(gp_script, "set label 'x2 (f2=f3)' at %f, 2.0 center front textcolor rgb 'blue'\n", x2);
    fprintf(gp_script, "set label 'x3 (f1=f2)' at %f, 6.5 center front textcolor rgb 'dark-green'\n\n", x3 - 0.1);
    
    // Добавляем горизонтальную линию y=0 для ориентира
    fprintf(gp_script, "set arrow from graph 0, first 0 to graph 1, first 0 nohead lt 1 lc rgb 'black' lw 1\n\n");
    
    // Добавляем текст с информацией о площади
    fprintf(gp_script, "# Информация о площади\n");
    fprintf(gp_script, "set label 10 sprintf('Площадь = %.6f', %f) at graph 0.5, graph 0.95 center front textcolor rgb 'dark-red' font 'Arial,16'\n\n", area, area);
    
    // Построение графиков
    fprintf(gp_script, "# Построение графиков\n");
    fprintf(gp_script, "plot ");
    fprintf(gp_script, "'f1_data.txt' using 1:2 with lines lw 3 lc rgb 'red' title 'f1(x) = 0.6x + 3', ");
    fprintf(gp_script, "'f2_data.txt' using 1:2 with lines lw 3 lc rgb 'blue' title 'f2(x) = (x-2)^3 - 1', ");
    fprintf(gp_script, "'f3_data.txt' using 1:2 with lines lw 3 lc rgb 'green' title 'f3(x) = 3/x', ");
    fprintf(gp_script, "'points_data.txt' using 1:2:3 with points pt 7 ps 2 lc variable title 'Точки пересечения'\n\n");
    
    // Создаем второй файл для интерактивного просмотра
    fprintf(gp_script, "# Интерактивный просмотр\n");
    fprintf(gp_script, "set terminal wxt size 1400,1000\n");
    fprintf(gp_script, "set output\n");
    fprintf(gp_script, "replot\n\n");
    
    // Добавляем команду для паузы
    fprintf(gp_script, "print '\\\nНажмите Enter для закрытия графиков...'\n");
    fprintf(gp_script, "pause mouse\n");
    
    fclose(gp_script);
    
    printf("\nСоздан скрипт gnuplot: plot_script.gp\n");
    printf("Сгенерированы файлы с данными для построения графиков.\n");
    
    // Пытаемся запустить gnuplot
    printf("Запуск gnuplot...\n");
    int result = system("gnuplot -persist plot_script.gp");
    
    if (result == 0) {
        printf("Графики успешно построены.\n");
        printf("Изображение сохранено в файл: functions_plot.png\n");
    } else {
        printf("Ошибка при запуске gnuplot. Убедитесь, что gnuplot установлен.\n");
        printf("Для просмотра графиков выполните: gnuplot -persist plot_script.gp\n");
    }
}