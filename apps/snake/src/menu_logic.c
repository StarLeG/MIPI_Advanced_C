#include "menu_logic.h"
#include "game_types.h"
#include "game_logic.h"
#include "graphics.h"
#include "sound.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

// Function to display start menu
int startMenu() {
    int selected_snake = 0; // 0 - first snake, 1 - second snake
    int selected_option = 0; // 0 - start game, 1 - restart, 2 - sound toggle, 3 - exit
    int color_index[NUM_SNAKES] = {0, 4}; // initial color indices

    // Array of available colors (using ncurses constants)
    int available_colors[] = {
        1, 2, 4, 3, 5, 6, 7  // GREEN, RED, BLUE, YELLOW, MAGENTA, CYAN, WHITE
    };
    char* color_names[] = {
        "Green", "Red", "Blue", "Yellow", "Magenta", "Cyan", "White"
    };
    int num_colors = 7;

    int key;

    while(1) {
        clear();

        // Title
        attron(A_BOLD);
        mvprintw(2, 10, "=== DOUBLE SNAKE GAME ===");
        attroff(A_BOLD);

        // Sound status
        mvprintw(3, 5, "Sound: %s", sound_enabled ? "ON" : "OFF");

        // Select snake for color configuration
        mvprintw(5, 5, "Select snake for color configuration:");
        for (int i = 0; i < NUM_SNAKES; i++) {
            if (i == selected_snake) {
                attron(A_REVERSE);
            }
            mvprintw(7, 5 + i * 20, "Snake %d", i + 1);
            if (i == selected_snake) {
                attroff(A_REVERSE);
            }
        }

        // Color selection for selected snake
        mvprintw(9, 5, "Color for snake %d:", selected_snake + 1);
        for (int i = 0; i < num_colors; i++) {
            attron(COLOR_PAIR(available_colors[i]));
            if (color_index[selected_snake] == i) {
                attron(A_REVERSE);
            }
            mvprintw(11, 5 + i * 12, "[%s]", color_names[i]);
            if (color_index[selected_snake] == i) {
                attroff(A_REVERSE);
            }
            attroff(COLOR_PAIR(available_colors[i]));
        }

        // Current control settings
        mvprintw(13, 5, "Current controls:");
        mvprintw(14, 8, "Snake 1: Arrow keys");
        mvprintw(15, 8, "Snake 2: WASD keys");

        // New mechanic
        mvprintw(16, 5, "New mechanic:");
        mvprintw(17, 8, "You can eat another snake! +50 points");

        // Menu options
        mvprintw(19, 5, "Options:");
        const char* options[] = {"Start Game", "Restart", "Sound ON/OFF", "Exit"};
        for (int i = 0; i < 4; i++) {
            if (i == selected_option) {
                attron(A_REVERSE);
            }
            mvprintw(21 + i, 8, "%s", options[i]);
            if (i == selected_option) {
                attroff(A_REVERSE);
            }
        }

        // Menu control instructions
        mvprintw(26, 5, "Menu controls:");
        mvprintw(27, 8, "Arrow keys UP/DOWN - navigation, ENTER - select, TAB - switch snakes");
        mvprintw(28, 8, "M - toggle sound");

        refresh();

        key = getch();

        switch(key) {
            case KEY_UP:
                selected_option = (selected_option - 1 + 4) % 4;
                break;
            case KEY_DOWN:
                selected_option = (selected_option + 1) % 4;
                break;
            case KEY_LEFT:
                if (selected_option == 0) {
                    color_index[selected_snake] = (color_index[selected_snake] - 1 + num_colors) % num_colors;
                }
                break;
            case KEY_RIGHT:
                if (selected_option == 0) {
                    color_index[selected_snake] = (color_index[selected_snake] + 1) % num_colors;
                }
                break;
            case '\t': // TAB
                selected_snake = (selected_snake + 1) % NUM_SNAKES;
                break;
            case 'm':
            case 'M':
                sound_enabled = !sound_enabled;
                if (sound_enabled) {
                    playSound(4); // Sound on sound
                }
                break;
            case '\n': // ENTER
            case '\r':
                // Save selected colors
                for (int i = 0; i < NUM_SNAKES; i++) {
                    snake_colors[i] = available_colors[color_index[i]];
                }

                if (selected_option == 0) {
                    playSound(4); // Game start sound
                    return 1; // Start game
                }
                if (selected_option == 1) return 2; // Restart
                if (selected_option == 2) {
                    sound_enabled = !sound_enabled;
                    if (sound_enabled) {
                        playSound(4); // Sound on sound
                    }
                    continue; // Stay in menu
                }
                if (selected_option == 3) return 0; // Exit
                break;
            case 'q':
            case 'Q':
                return 0; // Exit with Q
            case STOP_GAME:
                return 0; // Exit with F10
        }
    }
}

// Main game function
void playGame() {
    // Initialize two snakes
    snake_t snakes[NUM_SNAKES];
    initAllSnakes(snakes, NUM_SNAKES, START_TAIL_SIZE);

    // Get screen dimensions
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    // Create first food
    food_t food;
    spawnFood(&food, snakes, NUM_SNAKES, max_x, max_y);

    int key_pressed = 0;
    int game_over = 0;
    timeout(100);

    // Start background music (simulation)
    if (sound_enabled) {
        playSound(4); // Game start sound
    }

    // ==================== MAIN GAME LOOP ======================
    while (key_pressed != STOP_GAME && !game_over && game_running) {
        key_pressed = getch();          // read pressed key

        // Check sound toggle during game
        if (key_pressed == 'm' || key_pressed == 'M') {
            sound_enabled = !sound_enabled;
            mvprintw(2, 0, "Sound %s                  ", sound_enabled ? "ON" : "OFF");
        }

        changeAllDirections(snakes, NUM_SNAKES, key_pressed); // change direction

        // Move all snakes
        for (size_t i = 0; i < NUM_SNAKES; i++) {
            if (snakes[i].is_alive) {
                go(&snakes[i]);
                goTail(&snakes[i]);
            }
        }

        // Draw game field
        clear();
        // Display score
        mvprintw(0, 0, "P1: %d points | P2: %d points | M - sound | F10 - exit",
                 snakes[0].score, snakes[1].score);
        mvprintw(1, 0, "Controls: Arrows / WASD | Eat the other snake!");

        drawAllSnakes(snakes, NUM_SNAKES);
        drawFood(&food);

        // Check eaten food
        if (checkAllFood(snakes, NUM_SNAKES, &food))
            spawnFood(&food, snakes, NUM_SNAKES, max_x, max_y);

        // Check collisions (self-intersection enabled)
        if (checkAllCollisions(snakes, NUM_SNAKES, max_x, max_y)) {
            game_over = 1;
            playSound(3); // Game over sound
            
            // Immediately show game over screen and wait for key press
            clear();
            
            // Determine winner
            int winner = -1;
            int max_score = -1;
            int alive_count = 0;

            for (size_t i = 0; i < NUM_SNAKES; i++) {
                if (snakes[i].is_alive) {
                    alive_count++;
                    winner = i;
                }
                if (snakes[i].score > max_score) {
                    max_score = snakes[i].score;
                    winner = i;
                }
            }

            if (alive_count > 0) {
                // There is at least one alive snake
                mvprintw(max_y/2, (max_x-20)/2, "Snake %d wins!", winner + 1);
                mvprintw(max_y/2 + 1, (max_x-20)/2, "Score: %d points", snakes[winner].score);
            } else {
                // All snakes are dead
                mvprintw(max_y/2, (max_x-30)/2, "Game Over! All snakes died!");
                if (snakes[0].score == snakes[1].score) {
                    mvprintw(max_y/2 + 1, (max_x-9)/2, "Draw!");
                } else {
                    mvprintw(max_y/2 + 1, (max_x-20)/2, "Winner: Snake %d", winner + 1);
                }
            }

            mvprintw(max_y/2 + 2, (max_x-40)/2, "Press any key to return to menu...");
            refresh();
            
            // Wait for any key press
            timeout(-1); // Blocking wait
            getch();
            timeout(100); // Restore timeout
            
            break; // Exit game loop immediately
        }

        refresh();
        usleep(100000); // 100ms delay
    }

    // ==================== GAME CLEANUP ========================
    for (size_t i = 0; i < NUM_SNAKES; i++) {
        free(snakes[i].tail);
    }
    
    // Clear screen before returning to menu
    clear();
    refresh();
}
