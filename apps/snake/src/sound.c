#include "game_types.h"
#include "sound.h"
#include <stdio.h>
#include <unistd.h>

// Function to play sound signal
void playSound(int type) {
    if (!sound_enabled) return;

    switch(type) {
        case 1: // Food
            printf("\a"); // System beep
            fflush(stdout);
            break;
        case 2: // Snake eaten
            for(int i = 0; i < 3; i++) {
                printf("\a");
                fflush(stdout);
                usleep(100000);
            }
            break;
        case 3: // Game over
            for(int i = 0; i < 5; i++) {
                printf("\a");
                fflush(stdout);
                usleep(50000);
            }
            break;
        case 4: // Game start
            for(int i = 0; i < 2; i++) {
                printf("\a");
                fflush(stdout);
                usleep(200000);
            }
            break;
    }
}