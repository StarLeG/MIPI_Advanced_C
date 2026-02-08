#include "game_logic.h"
#include "game_types.h"
#include "sound.h"
#include <stdlib.h>
#include <string.h>

struct control_buttons default_controls[NUM_SNAKES] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},     // arrows for first snake
    {'s', 'w', 'a', 'd'}                         // WASD for second snake
};

int snake_colors[NUM_SNAKES] = {1, 6}; // GREEN and CYAN by default
int game_running = 1;
int can_eat_snakes = 1;
int sound_enabled = 1;

// Initialize tail (zero coordinates)
void initTail(tail_t t[], size_t size) {
    tail_t init_t = {0,0};
    for(size_t i=0; i<size; i++) t[i] = init_t;
}

// Initialize snake head
void initHead(snake_t *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = RIGHT; // initial direction right
    head->score = 0;
    head->is_alive = 1;
}

// Initialize whole snake
void initSnake(snake_t *head, size_t size, int x, int y, int color_pair) {
    tail_t *tail = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;
    head->tsize = size+1; // initial tail
    head->color_pair = color_pair;
}

// Initialize all snakes
void initAllSnakes(snake_t snakes[], size_t num_snakes, size_t start_size) {
    for (size_t i = 0; i < num_snakes; i++) {
        int start_x = 10 + i * 20;  // Different start positions
        int start_y = 10 + i * 5;
        initSnake(&snakes[i], start_size, start_x, start_y, snake_colors[i]);
        snakes[i].controls = default_controls[i];  // Different controls
    }
}

// Generate food at random position
void spawnFood(food_t *food, int max_x, int max_y) {
    food->x = rand() % max_x;
    food->y = (rand() % (max_y - MIN_Y)) + MIN_Y;
    food->symbol = '#'; // food symbol
}

// Check if snake ate food
int checkFood(snake_t *snake, food_t *food) {
    if(snake->x == food->x && snake->y == food->y) {
        snake->tsize++; // increase tail
        snake->score += 10; // add points
        playSound(1); // Food eating sound
        return 1;       // food eaten
    }
    return 0;
}

// Move snake head and draw
void go(snake_t *head) {
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // terminal sizes

    // Erase previous head position
    mvprintw(head->y, head->x, " ");

    // Move head depending on direction
    switch(head->direction){
        case LEFT:
            head->x = (head->x <= 0) ? max_x - 1 : head->x - 1;
            break;
        case RIGHT:
            head->x = (head->x >= max_x - 1) ? 0 : head->x + 1;
            break;
        case UP:
            head->y = (head->y <= MIN_Y) ? max_y - 1 : head->y - 1;
            break;
        case DOWN:
            head->y = (head->y >= max_y - 1) ? MIN_Y : head->y + 1;
            break;
    }
}

// Change direction for all snakes
void changeAllDirections(snake_t snakes[], size_t num_snakes, const int32_t key) {
    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue; // Skip dead snakes

        // For second snake (WASD) handle both English and Russian layouts
        if (i == 1) {
            // Handle WASD in any layout
            switch(key) {
                // English layout (lowercase)
                case 'w': case 'W':
                // Russian layout
                case 1094: case 1062: // Ц ц in Russian layout
                    snakes[i].direction = UP;
                    break;

                case 's': case 'S':
                // Russian layout
                case 1099: case 1067: // Ы ы in Russian layout
                    snakes[i].direction = DOWN;
                    break;

                case 'a': case 'A':
                // Russian layout
                case 1092: case 1060: // Ф ф in Russian layout
                    snakes[i].direction = LEFT;
                    break;

                case 'd': case 'D':
                // Russian layout
                case 1074: case 1042: // В в in Russian layout
                    snakes[i].direction = RIGHT;
                    break;
            }
        } else {
            // For first snake use arrows (layout independent)
            if (key == snakes[i].controls.down)
                snakes[i].direction = DOWN;
            else if (key == snakes[i].controls.up)
                snakes[i].direction = UP;
            else if (key == snakes[i].controls.right)
                snakes[i].direction = RIGHT;
            else if (key == snakes[i].controls.left)
                snakes[i].direction = LEFT;
        }
    }
}

// Move snake tail
void goTail(snake_t *head){
    if (!head->is_alive) return; // Don't move dead snake's tail

    // Erase last tail segment
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x," ");

    // Shift all tail segments
    for(size_t i = head->tsize-1; i>0; i--){
        head->tail[i] = head->tail[i-1];
    }

    // First tail segment takes previous head position
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

// Check food eating for all snakes
int checkAllFood(snake_t snakes[], size_t num_snakes, food_t *food) {
    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;
        if (checkFood(&snakes[i], food)) {
            return 1;
        }
    }
    return 0;
}

// Check head collision with own tail
int isCrush(snake_t *snake) {
    // Always return 0 to disable death from self-intersection
    return 0;
}

// Check screen boundary exit
int checkWallCollision(snake_t *snake, int max_x, int max_y) {
    if (snake->x < 0 || snake->x >= max_x || snake->y < MIN_Y || snake->y >= max_y) {
        return 1; // boundary collision
    }
    return 0;
}

// Check if one snake can eat another (catch from behind)
int checkSnakeEatSnake(snake_t snakes[], size_t num_snakes) {
    int snake_eaten = 0;

    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;

        for (size_t j = 0; j < num_snakes; j++) {
            if (i == j || !snakes[j].is_alive) continue; // Skip self and dead

            // Check if head of snake i is on position of snake j's head
            if (snakes[i].x == snakes[j].x && snakes[i].y == snakes[j].y) {
                // Snake i ate snake j
                snakes[j].is_alive = 0;
                snakes[i].score += 50; // Bonus for eating another snake
                snake_eaten = 1;
                playSound(2); // Snake eating sound

                // Display eating message
                int max_x = 0, max_y = 0;
                getmaxyx(stdscr, max_y, max_x);
                mvprintw(3, 0, "Snake %zd ate snake %zd! +50 points!", i + 1, j + 1);
            }

            // Check if head of snake i is on tail of snake j
            for (size_t k = 0; k < snakes[j].tsize; k++) {
                if (snakes[i].x == snakes[j].tail[k].x && snakes[i].y == snakes[j].tail[k].y) {
                    // Snake i ate part of snake j's tail
                    snakes[j].tsize = k; // Shorten snake j's tail
                    snakes[i].score += 20; // Bonus for eating tail
                    snake_eaten = 1;
                    playSound(1); // Tail eating sound

                    // Display tail eating message
                    int max_x = 0, max_y = 0;
                    getmaxyx(stdscr, max_y, max_x);
                    mvprintw(4, 0, "Snake %zd bit tail of snake %zd! +20 points!", i + 1, j + 1);
                    break;
                }
            }
        }
    }

    return snake_eaten;
}

// Check all collisions for all snakes
int checkAllCollisions(snake_t snakes[], size_t num_snakes, int max_x, int max_y) {
    int alive_count = 0;

    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;
        alive_count++;

        // Check wall collision (ENABLED)
        if (checkWallCollision(&snakes[i], max_x, max_y)) {
            snakes[i].is_alive = 0;
            playSound(3); // Wall collision sound
            mvprintw(2, 0, "Snake %zd crashed into wall!              ", i + 1);
        }

        // Check self-intersection (DISABLED - isCrush always returns 0)
        if (isCrush(&snakes[i])) {
            // This code never executes as isCrush always returns 0
            snakes[i].is_alive = 0;
        }
    }

    // Check snakes eating each other
    if (can_eat_snakes) {
        checkSnakeEatSnake(snakes, num_snakes);
    }

    // If only one snake or none left - game over
    return (alive_count <= 1);
}