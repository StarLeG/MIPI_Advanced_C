#include "findMaxBlock.h"

uint64_t findMaxBlock(list *head) {
    if (head == NULL) {
        return 0;
    }
    
    list *current = head;
    uint64_t max_address = head->address;
    size_t max_size = head->size;
    
    while (current != NULL) {
        if (current->size > max_size) {
            max_size = current->size;
            max_address = current->address;
        }
        current = current->next;
    }
    
    return max_address;
}

list* create_node(uint64_t address, size_t size) {
    list *new_node = (list*)malloc(sizeof(list));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->address = address;
    new_node->size = size;
    new_node->next = NULL;
    return new_node;
}

void add_to_end(list **head, uint64_t address, size_t size) {
    list *new_node = create_node(address, size);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    list *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(list *head) {
    list *current = head;
    while (current != NULL) {
        list *temp = current;
        current = current->next;
        free(temp);
    }
}