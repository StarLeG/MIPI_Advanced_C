#include "integral.h"
#include <stdio.h>
#include <math.h>

static int global_iterations = 0;

static double simpson(func_ptr f, double a, double b) {
    double c = (a + b) / 2;
    double h = (b - a) / 6;
    return h * (f(a) + 4 * f(c) + f(b));
}

static double adaptive_simpsons(func_ptr f, double a, double b, double eps, double whole, int depth) {
    global_iterations++;
    
    // Ограничение глубины рекурсии
    if (depth > 100) {
        return whole;
    }
    
    double c = (a + b) / 2;
    double left = simpson(f, a, c);
    double right = simpson(f, c, b);
    
    double error = fabs(left + right - whole);
    
    if (error < 15 * eps) {
        return left + right + (left + right - whole) / 15;
    }
    
    return adaptive_simpsons(f, a, c, eps / 2, left, depth + 1) + 
           adaptive_simpsons(f, c, b, eps / 2, right, depth + 1);
}

IntegralResult integral(func_ptr f, double a, double b, double eps2) {
    IntegralResult result = {0, 0, 0};
    global_iterations = 0;
    
    if (a >= b) {
        printf("Ошибка: Некорректный интервал [%f, %f]\n", a, b);
        return result;
    }
    
    // Проверка на особые точки для f3
    if (f == f3 && (a <= 0 || b <= 0)) {
        printf("Ошибка: f3 не определена при x <= 0\n");
        return result;
    }
    
    double whole = simpson(f, a, b);
    result.result = adaptive_simpsons(f, a, b, eps2, whole, 0);
    result.iterations = global_iterations;
    result.success = 1;
    
    return result;
}

void test_integral(void) {
    printf("\n=== Тестирование численного интегрирования ===\n");
    
    // Тест 1: ∫f1 от 0 до 1
    IntegralResult i1 = integral(f1, 0, 1, 1e-6);
    double expected1 = 3.3;
    printf("∫f1 от 0 до 1: %f, ожидание: %f, ошибка: %e, итераций: %d\n", 
           i1.result, expected1, fabs(i1.result - expected1), i1.iterations);
    
    // Тест 2: ∫f2 от 1 до 3
    IntegralResult i2 = integral(f2, 1, 3, 1e-6);
    double expected2 = -2.0;
    printf("∫f2 от 1 до 3: %f, ожидание: -2.0, ошибка: %e, итераций: %d\n", 
           i2.result, fabs(i2.result + 2.0), i2.iterations);
    
    // Тест 3: ∫f3 от 1 до 2
    IntegralResult i3 = integral(f3, 1, 2, 1e-6);
    double expected3 = 3 * log(2);
    printf("∫f3 от 1 до 2: %f, ожидание: %f, ошибка: %e, итераций: %d\n", 
           i3.result, expected3, fabs(i3.result - expected3), i3.iterations);
}