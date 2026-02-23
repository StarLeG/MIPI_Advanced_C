#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Прототипы функций
void print_help();

// Флаги для опций командной строки
int print_intersections = 0;
int print_iterations = 0;

int main(int argc, char* argv[]) {
    // Обработка аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-i") == 0) {
            print_intersections = 1;
        } else if (strcmp(argv[i], "-iter") == 0) {
            print_iterations = 1;
        } else {
            printf("Неизвестный ключ: %s\n", argv[i]);
            printf("Используйте -help для получения справки\n");
            return 1;
        }
    }
}

// Функция для вывода справки
void print_help() {
    printf("Программа для вычисления площади фигуры, образованной кривыми:\n");
    printf("f1 = 0.6x + 3\n");
    printf("f2 = (x - 2)^3 - 1\n");
    printf("f3 = 3 / x\n\n");
    printf("Допустимые ключи командной строки:\n");
    printf("  -help      - вывод этой справки\n");
    printf("  -i         - печать абсцисс точек пересечения кривых\n");
    printf("  -iter      - печать числа итераций для поиска точек пересечения\n");
}
