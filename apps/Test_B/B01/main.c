/*
                                Всего памяти
    Описана структура данных для хранения информации об использованной памяти:
        typedef struct list {
            void *address;
            size_t size;
            char comment[64];
            struct list *next;
        } list;
    Требуется реализовать только одну функцию, которая анализирует данный список и возвращает сколько всего памяти используется. Адрес хранится в поле address, поле size - соответствующий размер данного блока. Если список пустой, то функция должна возвращать 0.
    Прототип функции:

        size_t totalMemoryUsage(list *head)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

 typedef struct list {
            void *address;
            size_t size;
            char comment[64];
            struct list *next;
        } list;

size_t totalMemoryUsage(list *head) {
    size_t total = 0;
    
    for (list *current = head; current != NULL; current = current->next) {
        total += current->size;
    }
    
    return total;
}

list* createNode(void *address, size_t size, const char *comment) {
    list *newNode = (list*)malloc(sizeof(list));
    if (newNode == NULL) {
        return NULL;
    }
    
    newNode->address = address;
    newNode->size = size;
    if (comment != NULL) {
        snprintf(newNode->comment, sizeof(newNode->comment), "%s", comment);
    } else {
        newNode->comment[0] = '\0';
    }
    newNode->next = NULL;
    
    return newNode;
}

void freeList(list *head) {
    list *current = head;
    while (current != NULL) {
        list *next = current->next;
        free(current);
        current = next;
    }
}


int main(){

    int n;
    list *head = NULL;
    list *tail = NULL;

    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        unsigned long long addr;
        size_t size;

         if (scanf("%llu %zu", &addr, &size) != 2) {
            break;
        }

          list *newNode = createNode((void*)addr, size, "User input");
        if (newNode == NULL) {
            break;
        }

         if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

     size_t total = totalMemoryUsage(head);
    printf("%zu\n", total);

     freeList(head);
    
    return 0;
}