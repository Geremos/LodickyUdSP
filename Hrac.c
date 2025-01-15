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
Lodicka** getLode(Hrac* hrac){
    return hrac->lode;
}

// Pridanie lodičky do hráča
void add_ship(Hrac* hrac, Lodicka* lodicka)
{
    hrac->lode[lodicka->typLodicky - 2]++;
}

// Nastavenie mena hráča
void setHracMeno(Hrac* hrac, const char* meno) {
    strcpy(hrac->meno, meno);
}

// Inicializácia lodičky
void init_lodicka(Lodicka* lodicka, int start_x, int start_y, int end_x, int end_y, enum LodickaEnum typLodicky, bool spracovane) {
    lodicka->start_x = start_x;
    lodicka->start_y = start_y;
    lodicka->end_x = end_x;
    lodicka->end_y = end_y;
    lodicka->typLodicky = typLodicky;
    lodicka->spracovane = spracovane;
}

void nastav_lode_pre_hraca(Hrac* hrac) {
    // Počet lodí rôznych typov

    // Alokácia pamäte pre lode
    hrac->lode = malloc( 4 * sizeof(Lodicka*));
    int pom = Battlecruiser;
    // Pre každú veľkosť lode nastavíme lodí
    for (int i = 0; i < 4; i++) {
        hrac->lode[i] = malloc((i+1) * sizeof(Lodicka));
        for (int j = 0; j < i+1; j++) {
            init_lodicka(&hrac->lode[i][j], 0, 0, 0, 0, pom, false);
        }
        pom--;
    }
}

void destroy_lode(Hrac* hrac) {
    for (int i = 0; i < 4; i++) {
        free(hrac->lode[i]);
    }
    free(hrac->lode);
    hrac->lode = NULL;
}

bool are_all_ships_done(Hrac* hrac) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i+1; j++) {
            if (!hrac->lode[i][j].spracovane) {
                return false;
            }
        }
    }
    return true;
}

// Inicializácia hráča
void init_player(Hrac *player, const char *name) {
    strcpy(player->meno, name);
    player->meno[sizeof(player->meno) - 1] = '\0'; // Bezpečnostné ukončenie reťazca
    player->plocha = malloc(sizeof(HraciaPlocha));
    init_hraciaPlocha(player->plocha); // Inicializácia hracej plochy
    nastav_lode_pre_hraca(player);
    // Počet lodí každého typu na rozloženie
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
    bool lodicka_nastavena = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i+1; j++) {
            if (hrac->lode[i][j].typLodicky == typLodicky && !hrac->lode[i][j].spracovane && !lodicka_nastavena) {
                init_lodicka(&hrac->lode[i][j], zX, zY, kX, kY, typLodicky, true);
                lodicka_nastavena = true;
            }
        }
    }
    if (lodicka_nastavena) {
        for (int i = zX; i <= kX; i++) {
            for (int j = zY; j <= kY; j++) {
                hrac->plocha->hraciaPlocha[i][j].lodickaEnum = typLodicky;
            }
        }
        return true;
    }

    printf("Nie je dostupná loď tohto typu!\n");
    return false;
}

// Uvoľnenie pamäte hráča
void destroy_player(Hrac* hrac) {
    destroy_hraciaPlocha(hrac->plocha);
    destroy_lode(hrac);
}