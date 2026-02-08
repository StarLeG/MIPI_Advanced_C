#include "graphics.h"
#include "game_types.h"
#include <ncurses.h>

// Draw food on screen
void drawFood(food_t *food) {
    attron(COLOR_PAIR(8)); // Color for food (red)
    mvprintw(food->y, food->x, "%c", food->symbol);
    attroff(COLOR_PAIR(8));
}

// Draw all snakes with different colors
void drawAllSnakes(snake_t snakes[], size_t num_snakes) {
    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue; // Don't draw dead snakes

        attron(COLOR_PAIR(snakes[i].color_pair));  // Use selected color

        // Draw head
        mvprintw(snakes[i].y, snakes[i].x, "@");

        // Draw tail
        for (size_t j = 0; j < snakes[i].tsize; j++) {
            if (snakes[i].tail[j].y || snakes[i].tail[j].x) {
                mvprintw(snakes[i].tail[j].y, snakes[i].tail[j].x, "*");
            }
        }

        attroff(COLOR_PAIR(snakes[i].color_pair));
    }
}

// Function to display welcome screen
void showWelcomeScreen() {
    clear();

    // Title
    attron(A_BOLD);
    mvprintw(2, 15, "=== DOUBLE SNAKE GAME ===");
    attroff(A_BOLD);

    // Game description
    mvprintw(4, 5, "Welcome to 'Double Snake' game!");
    mvprintw(5, 5, "Control two snakes simultaneously and collect food.");

    // Main menu functions
    mvprintw(7, 5, "MAIN MENU FUNCTIONS:");
    mvprintw(8, 8, "• Color selection for each snake");
    mvprintw(9, 8, "• Control configuration");
    mvprintw(10, 8, "• Start game with selected settings");
    mvprintw(11, 8, "• Restart menu");
    mvprintw(12, 8, "• Sound on/off");
    mvprintw(13, 8, "• Exit game");

    // In-game controls
    mvprintw(15, 5, "IN-GAME CONTROLS:");
    mvprintw(16, 8, "Snake 1: Arrows ← ↑ → ↓");
    mvprintw(17, 8, "Snake 2: WASD (any layout)");
    mvprintw(18, 8, "Exit: F10");

    // Game features
    mvprintw(20, 5, "GAME FEATURES:");
    mvprintw(21, 8, "• Two independent snakes");
    mvprintw(22, 8, "• No death from self-intersection");
    mvprintw(23, 8, "• Teleportation through boundaries");
    mvprintw(24, 8, "• Colorful graphics");
    mvprintw(25, 8, "• Sound effects");
    mvprintw(26, 8, "• You can eat another snake if you catch it!");
    mvprintw(27, 8, "• +50 points for eating snake, +20 for tail");

    // Menu controls
    mvprintw(29, 5, "MENU CONTROLS:");
    mvprintw(30, 8, "Arrow keys ↑↓ - Navigate options");
    mvprintw(31, 8, "Arrow keys ←→ - Select color");
    mvprintw(32, 8, "TAB - Switch between snakes");
    mvprintw(33, 8, "ENTER - Select option");
    mvprintw(34, 8, "M - Toggle sound");
    mvprintw(35, 8, "Q or F10 - Exit");

    // Development info
    mvprintw(37, 5, "DEVELOPMENT:");
    mvprintw(38, 8, "Game created as educational project");
    mvprintw(39, 8, "using ncurses library");

    // Continue prompt
    attron(A_BOLD);
    mvprintw(41, 15, "Press any key to continue...");
    attroff(A_BOLD);

    refresh();
    getch(); // Wait for any key press
}