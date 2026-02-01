/*
                                        Циклический сдвиг
На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31).
Требуется циклически сдвинуть битычисла N вправо на K битов и вывести полученное таким образом число.
*/

#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t N;
    int K = 0;

    scanf("%u%d", &N, &K);

    if (K < 1 || K > 31) {
        printf("Invalid Input\n");
        return 1;
    }

    uint32_t result = 0;
    uint32_t bitsToMove = N & ((1U << K) - 1);

    uint32_t shiftedRight = N >> K;

    uint32_t movedBits = bitsToMove << (32 - K);

    result = shiftedRight | movedBits;

    printf("%u\n", result);

    return 0;
}