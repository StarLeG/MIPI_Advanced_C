#ifndef FINDMAXBLOCK_H
#define FINDMAXBLOCK_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct list {
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

uint64_t findMaxBlock(list *head);

list* create_node(uint64_t address, size_t size);
void add_to_end(list **head, uint64_t address, size_t size);
void free_list(list *head);

#endif // FINDMAXBLOCK_H