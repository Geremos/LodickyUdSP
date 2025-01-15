//
// Created by juraj on 14. 1. 2025.
//


#include "Hrac.h"

// Získanie hracej plochy hráča
HraciaPlocha* getHraciaPlocha(Hrac* hrac) {
    return hrac->plocha;
}

// Získanie mena hráča
char* getHracMeno(Hrac* hrac) {
    return hrac->meno;
}

// Získanie počtu lodí hráča
int* getLode(Hrac* hrac) {
    return hrac->lode;
}

// Nastavenie mena hráča
void setHracMeno(Hrac* hrac, const char* meno) {
    strcpy(hrac->meno, meno);
}

// Inicializácia hráča
void init_player(Hrac *player, const char *name) {
    strcpy(player->meno, name);
    player->meno[sizeof(player->meno) - 1] = '\0'; // Bezpečnostné ukončenie reťazca
    player->plocha = malloc(sizeof(HraciaPlocha));
    init_hraciaPlocha(player->plocha); // Inicializácia hracej plochy

    // Počet lodí každého typu na rozloženie
    player->lode[0] = 4; // 4 lode dĺžky 1
    player->lode[1] = 3; // 3 lode dĺžky 2
    player->lode[2] = 2; // 2 lode dĺžky 3
    player->lode[3] = 1; // 1 loď dĺžky 4
}

bool nastavLodicku(enum LodickaEnum typLodicky, int zX, int zY, int kX, int kY, Hrac* hrac)
{
    if (zX < 0 || zY < 0 || kX < 0 || kY < 0 || zX >= VELKOST_PLOCHY || zY >= VELKOST_PLOCHY || kX >= VELKOST_PLOCHY || kY >= VELKOST_PLOCHY)
    {
        return false;
    }
    if (zX > kX || zY > kY)
    {
        return false;
    }
    if (kX - zX != typLodicky - 1 && kY - zY != typLodicky - 1)
    {
        return false;
    }
    for (int i = zX; i <= kX; i++)
    {
        for (int j = zY; j <= kY; j++)
        {
            if (hrac->plocha->hraciaPlocha[i][j].lodickaEnum != noShip)
            {
                return false;
            }
        }
    }
    for (int i = zX; i <= kX; i++)
    {
        for (int j = zY; j <= kY; j++)
        {
            hrac->plocha->hraciaPlocha[i][j].lodickaEnum = typLodicky;
        }
    }
    return true;
}

bool are_all_ships_placed(Hrac *hrac) {
    for (int i = 0; i < 4; i++) {
        if (hrac->lode[i] > 0) {
            return false; // Niektoré lodičky ešte neboli rozložené
        }
    }
    return true;
}

// Uvoľnenie pamäte hráča
void destroy_player(Hrac* hrac) {
    destroy_hraciaPlocha(hrac->plocha);
}