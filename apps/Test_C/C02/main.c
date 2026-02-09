/*
    Польская запись
    Необходимо вычислить выражение написанное в обратной польской записи.
    На вход подается строка состоящая из целых, неотрицательных чисел и арифметических символов.
    В ответ единственное целое число - результат. Более подробно
    об Обратной польскаязапись числа можно также почитать тут:
    https://en.wikipedia.org/wiki/Reverse_Polish_notation
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

int main() {
    int stack[MAX_SIZE];
    int top = -1;
    char input[MAX_SIZE * 10];
    
    //printf("Enter RPN expression: ");
    fgets(input, sizeof(input), stdin);
    
    char* ptr = input;
    
    while (*ptr) {
        // Пропускаем пробелы
        while (*ptr == ' ') ptr++;
        
        if (!*ptr) break;
        
        // Если число
        if (isdigit(*ptr)) {
            int num = 0;
            while (isdigit(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            stack[++top] = num;
        }
        // Если оператор
        else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            if (top < 1) {
                printf("Invalid expression!\n");
                return 1;
            }
            
            int b = stack[top--];
            int a = stack[top--];
            int result;
            
            switch (*ptr) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Division by zero!\n");
                        return 1;
                    }
                    result = a / b; 
                    break;
            }
            
            stack[++top] = result;
            ptr++;
        }
        else {
            ptr++;
        }
    }
    
    if (top != 0) {
        printf("Invalid expression format!\n");
        return 1;
    }
    
    //printf("Result: %d\n", stack[top]);
    printf("%d\n", stack[top]);
    
    return 0;
}