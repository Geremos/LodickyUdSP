//
// Created by juraj on 14. 1. 2025.
//

#ifndef HRAC_H
#define HRAC_H
#include "HraciaPlocha.h"



typedef struct Lodicka{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    enum LodickaEnum typLodicky;
    bool spracovane;
} Lodicka;

// Štruktúra pre hráča
typedef struct Hrac {
    char meno[50];                 // Meno hráča
    HraciaPlocha* plocha;            // Hracia plocha hráča
    Lodicka** lode;         // Počet lodí každého typu, ktoré má hráč rozložiť
} Hrac;

// Funkcie na správu hráča
void init_hrac(Hrac *hrac, const char *name);
void destroy_hrac(Hrac* hrac);

void init_lodicka(Lodicka* lodicka, int start_x, int start_y, int end_x, int end_y, enum LodickaEnum typLodicky, bool spracovane);

bool nastavLodicku(enum LodickaEnum typLodicky, int zX, int zY, int kX, int kY, Hrac* hrac);
HraciaPlocha* getHraciaPlocha(Hrac* hrac);
const char* getHracMeno(Hrac* hrac);
Lodicka** getLode(Hrac* hrac);
void destroy_Lode(Hrac* hrac);
void setHracMeno(Hrac* hrac, const char* meno);
bool are_all_ships_placed(Hrac *hrac);
#endif //HRAC_H
