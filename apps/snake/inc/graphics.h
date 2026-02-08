#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game_types.h"

// Drawing functions
void drawFood(food_t *food);
void drawAllSnakes(snake_t snakes[], size_t num_snakes);

// Screen functions
void showWelcomeScreen();

#endif /* GRAPHICS_H */