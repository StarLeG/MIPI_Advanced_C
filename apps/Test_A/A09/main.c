/*
                Упаковать массив
    В программе реализована структура данных:
        struct pack_array {
            uint32_t array; // поле для хранения упакованного массива из 0 и 1
            uint32_t count0 : 8; // счетчик нулей в array
            uint32_t count1 : 8; // счетчик единиц в array
        }
    Необходимо реализовать программу, которая упаковывает переданный ей массив из 32-ух элементов 0 и 1 в указанную структуру данных.
    Функция должна строго соответствовать прототипу:

    void array2struct(int [], struct pack_array *)
*/

#include <stdio.h>
#include <stdint.h>

struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
};

void array2struct(int arr[], struct pack_array *packed) {
    packed->array = 0;
    packed->count0 = 0;
    packed->count1 = 0;

    for (int i = 0; i < 32; i++) {
        if (arr[i] == 1) {            
            packed->array |= (1U << (31 - i));
            packed->count1++;
        } else {
            packed->count0++;
        }
    }
}

int main() {
    int arr[32];
     for (int i = 0; i < 32; i++) {
        scanf("%d", &arr[i]);
    }

    struct pack_array packed;
    array2struct(arr, &packed);

    printf("%u ", packed.array);
    printf("%u ", packed.count0);
    printf("%u\n", packed.count1);

    return 0;
}