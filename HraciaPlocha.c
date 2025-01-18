//
// Created by juraj on 13. 1. 2025.
//
//
// Created by juraj on 12. 1. 2025.
//

#include "HraciaPlocha.h"

#include <stdio.h>
#include <stdlib.h>

// Tlačidlá pre hraciu plochu
void init_hraciaPlocha(HraciaPlocha* hraciaPlocha)
{
    if (!hraciaPlocha) return;

    // Vytvorenie generickej matice pre políčka
    hraciaPlocha->hraciaPlocha = create_matrix(VELKOST_PLOCHY, VELKOST_PLOCHY, sizeof(Policko));
    if (!hraciaPlocha->hraciaPlocha) {
        free(hraciaPlocha);
        return;
    }

    // Inicializácia políčok
    for (size_t i = 0; i < VELKOST_PLOCHY; i++) {
        for (size_t j = 0; j < VELKOST_PLOCHY; j++) {
            Policko policko; // Lokálny objekt
            init_Policko(&policko, i, j); // Inicializujeme hodnoty
            set_element(hraciaPlocha->hraciaPlocha, i, j, &policko); // Uložíme do matice
        }
    }
}

void destroy_hraciaPlocha(HraciaPlocha* hraciaPlocha)
{
    if (!hraciaPlocha) return;
    // Uvoľnenie generickej matice
    destroy_matrix(hraciaPlocha->hraciaPlocha);
    free(hraciaPlocha);
}

Policko* getPolicko(int x, int y, HraciaPlocha* hraciaPlocha)
{
    if (!hraciaPlocha || x < 0 || x >= VELKOST_PLOCHY || y < 0 || y >= VELKOST_PLOCHY) {
        printf("Chyba: Neplatné súradnice (%d, %d)\n", x, y);
        return NULL;
    }
    return (Policko*)get_element(hraciaPlocha->hraciaPlocha, x, y);
}

void setTypPolickaNaPloche(enum TypPolickaEnum typ, int x, int y, HraciaPlocha* hraciaPlocha)
{
    if (!hraciaPlocha || x < 0 || x >= VELKOST_PLOCHY || y < 0 || y >= VELKOST_PLOCHY) {
        printf("Chyba: Neplatné súradnice (%d, %d)\n", x, y);
        return;
    }
    Policko policko = *(Policko*)get_element(hraciaPlocha->hraciaPlocha, x, y);
    setTypPolicka(typ, &policko );
    set_element(hraciaPlocha->hraciaPlocha, x, y, &policko);
}






