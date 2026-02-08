#include "main.h"

int main()
{
   srand(time(NULL)); // random number generator

    // Initialize curses
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);

    // Check color support
    if(!has_colors()){
        endwin();
        printf("Your terminal does not support colors\n");
        return 1;
    }

    // Enable color and set color pairs
    start_color();
    // Use standard ncurses color constants
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);    // Food

    // Show welcome screen on startup
    showWelcomeScreen();

    // Main program loop
    while (game_running) {
        int menu_result = startMenu();

        if (menu_result == 1) {
            // Start game
            playGame();
        } else if (menu_result == 2) {
            // Restart (do nothing, just continue loop)
            continue;
        } else {
            // Exit
            game_running = 0;
        }
    }

    endwin(); // end curses mode
    return 0;    
}