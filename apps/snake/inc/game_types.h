#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <ncurses.h>
#include <inttypes.h>

#define NUM_SNAKES 2
#define MIN_Y  2  // Minimum Y coordinate to avoid writing over instructions
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

// Structure for control keys
struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

// Standard control keys
extern struct control_buttons default_controls[NUM_SNAKES];

// Structure for one tail segment
typedef struct tail_t {
    int x;
    int y;
} tail_t;

// Snake structure
typedef struct snake_t {
    int x;  // head X coordinate
    int y;  // head Y coordinate
    int direction; // movement direction
    size_t tsize;  // current tail size
    struct tail_t *tail; // tail array
    struct control_buttons controls; // control keys
    int color_pair; // snake color
    int score;      // player score
    int is_alive;   // whether snake is alive
} snake_t;

// Food structure
typedef struct food_t {
    int x;
    int y;
    char symbol;
} food_t;

// Global settings variables
extern int snake_colors[NUM_SNAKES];
extern int game_running;
extern int can_eat_snakes;
extern int sound_enabled;

#endif /* GAME_TYPES_H */