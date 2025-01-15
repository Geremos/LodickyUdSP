//
// Created by juraj on 12. 1. 2025.
//

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "GUI.h"
#include "Hrac.h"
// Štruktúra na reprezentáciu stavu hry
typedef struct GameState {
    Hrac* hrac;                // Hráč
    Hrac* opponent;              // Oponent
    int hrac_score;            // Skóre hráča
    int opponent_score;          // Skóre oponenta
    bool game_over;              // Indikácia konca hry
} GameState;

// Funkcie pre inicializáciu a správu stavu hry
void initialize_game_state(GameState *state, char* player_name);
bool is_game_over(GameState *state);
void initialize_css();


#endif //GAME_LOGIC_H
//kjf