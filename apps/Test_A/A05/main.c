/*
                                Подсчет битов
    На вход программе подается беззнаковое 32-битное целое число N.
    Требуется найти количество единичных битов в двоичном представлении данного числа.
*/

#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t N;
    scanf("%u", &N);
    
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (N & (1U << i)) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}