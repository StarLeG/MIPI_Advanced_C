/*
    Максимальный блок
    Описана структура данных

        typedef struct list {
            uint64_t address;
            size_t size;
            char comment[64];
            struct list *next;
        } list;

    Требуется реализовать только одну функцию, которая в данном списке находит адрес блока памяти занимающий больше всего места.
    Адрес хранится в поле address, поле size - соответствующий размер данного блока. Если список пустой, то функция должна возвращать 0. Если есть несколько таких блоков, то вернуть адрес любого из них.
    Прототип функции:

        uint64_t findMaxBlock(list *head)
*/

#include <stdio.h>
#include "findMaxBlock.h"


int main() {
    int n;
    list *head = NULL;
        
    scanf("%d", &n);
        
    for (int i = 0; i < n; i++) {
        uint64_t address;
        size_t size;
        scanf("%lu %zu", &address, &size);
        add_to_end(&head, address, size);
    }
        
    uint64_t max_block_address = findMaxBlock(head);
        
    printf("%lu\n", max_block_address);
      
    free_list(head);
    
    return 0;
}
