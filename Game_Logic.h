//
// Created by juraj on 12. 1. 2025.
//

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "HraciaPlocha.h"

// Štruktúra na reprezentáciu stavu hry
typedef struct GameState {
    HraciaPlocha player_board;   // Plocha hráča
    HraciaPlocha opponent_board; // Plocha oponenta
    int player_score;            // Skóre hráča
    int opponent_score;          // Skóre oponenta
    bool game_over;              // Indikácia konca hry
} GameState;

// Funkcie pre inicializáciu a správu stavu hry
void initialize_game_state(GameState *state);
bool player_shoot(GameState *state, int x, int y);
bool opponent_shoot(GameState *state, int x, int y);
bool is_game_over(GameState *state);
#endif //GAME_LOGIC_H
//kjf