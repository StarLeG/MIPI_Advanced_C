/*
										Извлечение бит
На вход программе подается беззнаковое 32-битное целое число N и натуральное число K (1 ≤ K ≤ 31).
Требуется взять K младших битов числа N и вывести полученное таким образом число.
*/

#include <stdio.h>
#include <stdint.h>

int main(void) {

	uint32_t N;
	int K;
	scanf("%u %d", &N, &K);

	uint32_t result = N & ((1U << K) - 1);

	printf("%u\n", result);

	return 0;
}