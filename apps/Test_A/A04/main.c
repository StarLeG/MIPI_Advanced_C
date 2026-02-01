/*
                                    Поиск последовательности бит
    На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31).
    Требуется взять K подряд идущих битов числа N так, чтобы полученное число было максимальным.
    Программа должна вывести полученное число.
*/

#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t N;
    int K;
    scanf("%u %d", &N, &K);
    
    uint32_t max_value = 0;
        
    for (int i = 0; i <= 32 - K; i++) {
        uint32_t shifted = N >> i;             
        uint32_t value = shifted & ((1U << K) - 1);        
       
        if (value > max_value) {
            max_value = value;
        }
    }
    
    printf("%u\n", max_value);
    return 0;
}