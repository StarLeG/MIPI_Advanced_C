#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_types.h"

// Snake initialization functions
void initTail(tail_t t[], size_t size);
void initHead(snake_t *head, int x, int y);
void initSnake(snake_t *head, size_t size, int x, int y, int color_pair);
void initAllSnakes(snake_t snakes[], size_t num_snakes, size_t start_size);

// Food functions
void spawnFood(food_t *food, snake_t snakes[], size_t num_snakes, int max_x, int max_y);
int checkFood(snake_t *snake, food_t *food);
int checkAllFood(snake_t snakes[], size_t num_snakes, food_t *food);

// Movement functions
void go(snake_t *head);
void goTail(snake_t *head);
void changeAllDirections(snake_t snakes[], size_t num_snakes, const int32_t key);

// Collision functions
int isCrush(snake_t *snake);
int checkWallCollision(snake_t *snake, int max_x, int max_y);
int checkSnakeEatSnake(snake_t snakes[], size_t num_snakes);
int checkAllCollisions(snake_t snakes[], size_t num_snakes, int max_x, int max_y);

#endif /* GAME_LOGIC_H */