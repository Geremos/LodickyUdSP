//
// Created by juraj on 13. 1. 2025.
//
#include "game_logic.h"
#include <stdbool.h>

void initialize_game_state(GameState *state) {
    // Inicializácia hráčskej a súperovej plochy
    init_hraciaPlocha(&state->player_board);
    init_hraciaPlocha(&state->opponent_board);

    state->player_score = 0;
    state->opponent_score = 0;
    state->game_over = false;
}

bool is_game_over(GameState *state) {
    // Logika na kontrolu konca hry (napr. zničené všetky lode)
    return state->game_over;
}


