#include "root.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

static int global_iterations = 0;

RootResult root(func_ptr f, func_ptr g, double a, double b, double eps1) {
    RootResult result = {0, 0, 0};
    global_iterations = 0;
    
    // Проверка корректности интервала
    if (a >= b) {
        printf("Ошибка: левая граница больше правой [%f, %f]\n", a, b);
        return result;
    }
    
    double fa = f(a) - g(a);
    double fb = f(b) - g(b);
    
    // Если значения на концах одинакового знака, пробуем найти подынтервалы
    if (fa * fb > 0) {
        // Увеличиваем количество шагов для более тщательного поиска
        int num_steps = 1000;
        double step = (b - a) / num_steps;
        double x_prev = a;
        double f_prev = fa;
        int found = 0;
        
        for (int i = 1; i <= num_steps; i++) {
            double x_curr = a + i * step;
            double f_curr = f(x_curr) - g(x_curr);
            
            // Проверяем смену знака
            if (f_prev * f_curr <= 0 && fabs(f_prev) > 1e-15 && fabs(f_curr) > 1e-15) {
                // Нашли интервал со сменой знака
                a = x_prev;
                b = x_curr;
                fa = f_prev;
                fb = f_curr;
                found = 1;
                break;
            }
            
            // Также проверяем близость к нулю (возможно функция касается оси)
            if (fabs(f_curr) < eps1) {
                result.root = x_curr;
                result.iterations = i;
                result.success = 1;
                return result;
            }
            
            x_prev = x_curr;
            f_prev = f_curr;
        }
        
        // Если не нашли корень в заданном интервале, просто возвращаем результат с ошибкой
        if (!found) {
            // Не выводим предупреждение для заведомо пустых интервалов
            // При тестировании левого корня f1=f2 это нормально
            return result;
        }
    }
    
    double c = a;
    double fc;
    double prev_c = a;
    
    for (int i = 0; i < 1000; i++) {
        global_iterations++;
        
        // Метод секущих
        if (fabs(fb - fa) > 1e-15) {
            c = b - fb * (b - a) / (fb - fa);
        } else {
            c = (a + b) / 2;
        }
        
        // Проверка на выход за границы
        if (c < a || c > b) {
            c = (a + b) / 2;
        }
        
        fc = f(c) - g(c);
        
        // Проверка сходимости
        if (fabs(fc) < eps1 || fabs(b - a) < eps1 || fabs(c - prev_c) < eps1) {
            result.root = c;
            result.iterations = global_iterations;
            result.success = 1;
            return result;
        }
        
        prev_c = c;
        
        // Обновление интервала
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else if (fb * fc < 0) {
            a = c;
            fa = fc;
        } else {
            // Если неопределенность, берем середину
            c = (a + b) / 2;
            fc = f(c) - g(c);
            if (fa * fc < 0) {
                b = c;
                fb = fc;
            } else {
                a = c;
                fa = fc;
            }
        }
    }
    
    result.root = c;
    result.iterations = global_iterations;
    // Не отмечаем как успех, если не сошлись за 1000 итераций
    return result;
}

// Вспомогательная функция для поиска всех корней
RootResult find_root_f1_f2_left(double eps1) {
    return root(f1, f2, -5, -4, eps1);
}

void test_root(void) {
    printf("\n=== Тестирование поиска корня ===\n");
    
    // Тест для f1=f2 (левый корень) - ожидаемо не найден
    RootResult r12_left = find_root_f1_f2_left(1e-6);
    printf("f1 = f2 (левый): корень = %f, итераций = %d, успех = %d (ожидаемо не найден)\n", 
           r12_left.root, r12_left.iterations, r12_left.success);
    if (r12_left.success) {
        printf("  Проверка: f1-f2 = %e\n", f1(r12_left.root) - f2(r12_left.root));
    }
    
    // Тест для f1=f2 (правый корень)
    RootResult r12_right = root(f1, f2, 0, 10, 1e-6);
    printf("f1 = f2 (правый): корень = %f, итераций = %d, успех = %d\n", 
           r12_right.root, r12_right.iterations, r12_right.success);
    printf("  Проверка: f1-f2 = %e\n", f1(r12_right.root) - f2(r12_right.root));
    
    // Тест для f1=f3
    RootResult r13 = root(f1, f3, 0.1, 5, 1e-6);
    printf("f1 = f3: корень = %f, итераций = %d, успех = %d\n", 
           r13.root, r13.iterations, r13.success);
    printf("  Проверка: f1-f3 = %e\n", f1(r13.root) - f3(r13.root));
    
    // Тест для f2=f3
    RootResult r23 = root(f2, f3, 0.1, 5, 1e-6);
    printf("f2 = f3: корень = %f, итераций = %d, успех = %d\n", 
           r23.root, r23.iterations, r23.success);
    printf("  Проверка: f2-f3 = %e\n", f2(r23.root) - f3(r23.root));
}