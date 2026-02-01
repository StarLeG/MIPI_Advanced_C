/*
                Распаковать порядок
    Необходимо реализовать программу, которой на входе передаётся вещественное число в типе float,
    она возвращает порядок который хранится в поле EXP в виде десятичного целого числа.
    Функция должна строго соответствовать прототипу

    int extractExp(float)
*/

#include <stdint.h>
#include <stdio.h>

int extractExp(float num) {

    uint32_t bits = *(uint32_t*)&num;
    int exp = (bits >> 23) & 0xFF;    
    return exp;
}


int main() {
    float num;
    scanf("%f", &num);
    int exp = extractExp(num);
    printf("%d\n", exp);
    return 0;
}