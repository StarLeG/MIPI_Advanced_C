#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include <unistd.h>


typedef struct Snake_t {
    int x;
    int y;
    int direction;
    int length;
    struct Tail_t* next;
    struct ControlButton* ControlButton;
} Snake_t;

typedef struct ControlButton {
    int up;
    int down;
    int left;
    int right;
} ControlButton;

typedef struct Tail_t {
    int x;
    int y;    
} Tail_t;


#endif /* MAIN_H */