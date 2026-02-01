/*
    На стандартном потоке ввода задаётся натуральное число N (N > 0), после которого следует последовательность из N целых чисел.
    На стандартный поток вывода напечатайте, сколько раз в этой последовательности встречается максимум.
    Указание: использовать массивы запрещается.
*/


#include <stdio.h>

int main() {
    int N = 0;
    int max = 0;
    int cnt = 0;
    int current = 0;

    scanf("%d", &N);

    if(N <= 0) return 1;

    scanf("%d", &current);
    max = current;
    cnt = 1;

    for(int i = 1; i < N; i++){
        scanf("%d", &current);

        if(current > max){
            max = current;
            cnt = 1;
        }else if(current == max){
            cnt++;
        }
    }

    printf("%d\n", cnt);

    return 0;
}