//
// Created by juraj on 14. 1. 2025.
//

#ifndef HRAC_H
#define HRAC_H
#include "HraciaPlocha.h"

// Štruktúra pre hráča
typedef struct Hrac {
    char meno[50];                 // Meno hráča
    HraciaPlocha* plocha;            // Hracia plocha hráča
    int lode[4];         // Počet lodí každého typu, ktoré má hráč rozložiť
} Hrac;

// Funkcie na správu hráča
void init_player(Hrac *player, const char *name);
bool nastavLodicku(enum LodickaEnum typLodicky, int zX, int zY, int kX, int kY, Hrac* hrac);
HraciaPlocha* getHraciaPlocha(Hrac* hrac);
char* getHracMeno(Hrac* hrac);
int* getLode(Hrac* hrac);
void setHracMeno(Hrac* hrac, const char* meno);
void setLode(Hrac* hrac, int lode[4]);
void destroy_player(Hrac* hrac);
bool are_all_ships_placed(Hrac *hrac);
#endif //HRAC_H
