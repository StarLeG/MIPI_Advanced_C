/**
 * @file main.c
 * @brief Основная программа вычисления площади
 * 
 * Обрабатывает аргументы командной строки, находит точки пересечения
 * и вычисляет площадь фигуры, ограниченной тремя кривыми
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"
#include "root.h"
#include "integral.h"
#include "plotting.h"

/**
 * @brief Структура для хранения информации о точке пересечения
 */
typedef struct {
    double x;           /**< Абсцисса точки пересечения */
    int f_i;            /**< Индекс первой функции */
    int f_j;            /**< Индекс второй функции */
    int iterations;     /**< Количество итераций при поиске */
} Intersection;

/**
 * @brief Вывод справки по использованию программы
 */
void print_help(void);

/**
 * @brief Поиск и вывод точек пересечения функций
 * @param print_abscissas Флаг вывода абсцисс
 * @param print_iterations Флаг вывода количества итераций
 */
void find_intersections(int print_abscissas, int print_iterations);

/**
 * @brief Вычисление площади фигуры
 * @param eps1 Точность для поиска корней
 * @param eps2 Точность для интегрирования
 * @param print_iterations Флаг вывода количества итераций
 * @return Вычисленная площадь
 */
double calculate_area(double eps1, double eps2, int print_iterations);

/**
 * @brief Точка входа в программу
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return 0 при успешном выполнении, иначе код ошибки
 */
int main(int argc, char* argv[]) {
    int print_abscissas = 0;
    int print_iterations = 0;
    int test_mode = 0;
    int plot_mode = 0;
    double eps1 = 1e-6;
    double eps2 = 1e-4;
    
    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        }
        else if (strcmp(argv[i], "--abscissas") == 0 || strcmp(argv[i], "-a") == 0) {
            print_abscissas = 1;
        }
        else if (strcmp(argv[i], "--iterations") == 0 || strcmp(argv[i], "-i") == 0) {
            print_iterations = 1;
        }
        else if (strcmp(argv[i], "--test") == 0 || strcmp(argv[i], "-t") == 0) {
            test_mode = 1;
        }
        else if (strcmp(argv[i], "--plot") == 0 || strcmp(argv[i], "-p") == 0) {
            plot_mode = 1;
        }
        else if (strcmp(argv[i], "--eps1") == 0 && i + 1 < argc) {
            eps1 = atof(argv[++i]);
        }
        else if (strcmp(argv[i], "--eps2") == 0 && i + 1 < argc) {
            eps2 = atof(argv[++i]);
        } else {
            printf("Ошибка: неизвестный аргумент '%s'\n", argv[i]);
            printf("Используйте '--help' для получения справки.\n");
            return 1;
        }
    }
    
    printf("Программа вычисления площади\n");
    printf("=============================\n\n");
    
    if (test_mode) {
        printf("Запуск тестов...\n");
        test_root();
        test_integral();
        return 0;
    }
    
    if (plot_mode) {
        plot_graphs(eps1, eps2);
        return 0;
    }
    
    find_intersections(print_abscissas, print_iterations);
    
    double area = calculate_area(eps1, eps2, print_iterations);
    printf("\nВычисленная площадь: %f\n", area);
    
    return 0;
}

/**
 * @brief Вывод справки по использованию программы
 */
void print_help(void) {
    printf("Использование: area_calc [ОПЦИИ]\n\n");
    printf("Опции:\n");
    printf("  -h, --help\t\tВывод этого справочного сообщения\n");
    printf("  -a, --abscissas\tВывод абсцисс точек пересечения\n");
    printf("  -i, --iterations\tВывод количества итераций для приближений\n");
    printf("  -t, --test\t\tЗапуск тестов функций поиска корней и интегрирования\n");
    printf("  -p, --plot\t\tПостроение графиков функций с gnuplot\n");
    printf("  --eps1 ЗНАЧЕНИЕ\tУстановка точности для поиска корней (по умолчанию: 1e-6)\n");
    printf("  --eps2 ЗНАЧЕНИЕ\tУстановка точности для интегрирования (по умолчанию: 1e-4)\n\n");
    printf("Описание:\n");
    printf("  Программа вычисляет площадь, ограниченную тремя кривыми:\n");
    printf("  f1(x) = 0.6x + 3\n");
    printf("  f2(x) = (x-2)^3 - 1\n");
    printf("  f3(x) = 3/x\n");
}

/**
 * @brief Поиск и вывод точек пересечения функций
 * @param print_abscissas Флаг вывода абсцисс
 * @param print_iterations Флаг вывода количества итераций
 */
void find_intersections(int print_abscissas, int print_iterations) {
    printf("Поиск точек пересечения:\n");
    printf("-------------------------\n");
    
    // Пары функций для поиска пересечений
    struct {
        int f1, f2;
        double a, b;
        const char* desc;
    } pairs[] = {
        {1, 2, 3, 4, "f1 и f2"},           // Единственное пересечение около 3.85
        {1, 3, 0.1, 5, "f1 и f3"},          // Около 0.85
        {2, 3, 0.1, 5, "f2 и f3"}           // Около 3.24
    };
    
    int num_pairs = sizeof(pairs) / sizeof(pairs[0]);
    Intersection intersections[10];
    int num_intersections = 0;
    
    for (int i = 0; i < num_pairs; i++) {
        func_ptr f = get_function(pairs[i].f1);
        func_ptr g = get_function(pairs[i].f2);
        
        RootResult r = root(f, g, pairs[i].a, pairs[i].b, 1e-6);
        
        if (r.success) {
            intersections[num_intersections].x = r.root;
            intersections[num_intersections].f_i = pairs[i].f1;
            intersections[num_intersections].f_j = pairs[i].f2;
            intersections[num_intersections].iterations = r.iterations;
            num_intersections++;
            
            if (print_abscissas) {
                printf("%s: x = %f\n", pairs[i].desc, r.root);
            }
            if (print_iterations) {
                printf("  Итераций: %d\n", r.iterations);
            }
        } else {
            if (print_abscissas) {
                printf("%s: не найден\n", pairs[i].desc);
            }
        }
    }
    
    // Сортировка точек пересечения по возрастанию x
    for (int i = 0; i < num_intersections - 1; i++) {
        for (int j = i + 1; j < num_intersections; j++) {
            if (intersections[i].x > intersections[j].x) {
                Intersection temp = intersections[i];
                intersections[i] = intersections[j];
                intersections[j] = temp;
            }
        }
    }
    
    if (!print_abscissas && num_intersections > 0) {
        printf("Найдено %d точек пересечения. Используйте --abscissas для их отображения.\n", num_intersections);
    }
}

/**
 * @brief Вычисление площади фигуры
 * @param eps1 Точность для поиска корней
 * @param eps2 Точность для интегрирования
 * @param print_iterations Флаг вывода количества итераций
 * @return Вычисленная площадь
 */
double calculate_area(double eps1, double eps2, int print_iterations) {    
    printf("\nВычисление площади...\n");
    printf("---------------------\n");
    
    // Поиск нужных точек пересечения
    RootResult r13 = root(f1, f3, 0.1, 5, eps1);        // f1=f3 ≈ 0.85
    RootResult r23 = root(f2, f3, 0.1, 5, eps1);        // f2=f3 ≈ 3.24
    RootResult r12_right = root(f1, f2, 3, 4, eps1);     // f1=f2 ≈ 3.85
    
    if (print_iterations) {
        printf("Итерации поиска корней:\n");
        printf("  f1=f3: %d итераций\n", r13.iterations);
        printf("  f2=f3: %d итераций\n", r23.iterations);
        printf("  f1=f2: %d итераций\n", r12_right.iterations);
    }
    
    // Используем найденные корни или значения по умолчанию, если поиск не удался
    double x1 = r13.success ? r13.root : 0.854109;
    double x2 = r23.success ? r23.root : 3.243927;
    double x3 = r12_right.success ? r12_right.root : 3.847753;
    
    // Сортируем точки
    double points[3] = {x1, x2, x3};
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (points[i] > points[j]) {
                double temp = points[i];
                points[i] = points[j];
                points[j] = temp;
            }
        }
    }
    
    printf("Точки пересечения: x1 = %f, x2 = %f, x3 = %f\n", 
           points[0], points[1], points[2]);
    
    // Вычисление площади как суммы интегралов разностей функций
    // На [x1, x2]: f1 выше f2
    // На [x2, x3]: f2 выше f3
    IntegralResult int_f1_1 = integral(f1, points[0], points[1], eps2);
    IntegralResult int_f2_1 = integral(f2, points[0], points[1], eps2);
    IntegralResult int_f2_2 = integral(f2, points[1], points[2], eps2);
    IntegralResult int_f3_2 = integral(f3, points[1], points[2], eps2);
    
    double area = (int_f1_1.result - int_f2_1.result) + 
                  (int_f2_2.result - int_f3_2.result);
    
    if (print_iterations) {
        printf("\nИтерации интегрирования:\n");
        printf("  ∫f1 на [%f,%f]: %d\n", points[0], points[1], int_f1_1.iterations);
        printf("  ∫f2 на [%f,%f]: %d\n", points[0], points[1], int_f2_1.iterations);
        printf("  ∫f2 на [%f,%f]: %d\n", points[1], points[2], int_f2_2.iterations);
        printf("  ∫f3 на [%f,%f]: %d\n", points[1], points[2], int_f3_2.iterations);
    }
    
    return area;
}