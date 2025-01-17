#include <stdio.h>

// Entry point of the program
#include "Game_Logic.h"

int main(int argc, char *argv[]) {
    GameState state;
    gtk_init(&argc, &argv);
    //printf("GTK version: %d.%d.%d\n", gtk_get_major_version(), gtk_get_minor_version(), gtk_get_micro_version());
    initialize_game_state(&state, "Juraj");
    return 0;
}













