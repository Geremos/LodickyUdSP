//
// Created by juraj on 13. 1. 2025.
//
//
// Created by juraj on 12. 1. 2025.
//

#include "HraciaPlocha.h"

#include <stdlib.h>

// Tlačidlá pre hraciu plochu
void init_hraciaPlocha(HraciaPlocha* hraciaPlocha)
{
    hraciaPlocha->hraciaPlocha = (Policko**)malloc(VELKOST_PLOCHY * sizeof(Policko*));
    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        hraciaPlocha->hraciaPlocha[i] = (Policko*)malloc(VELKOST_PLOCHY * sizeof(Policko));
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            init_Policko(&hraciaPlocha->hraciaPlocha[i][j], i, j);
        }
    }
}

// Policko* getPolicko(int x, int y, HraciaPlocha* hraciaPlocha)
// {
//     if (x < 0 || x >= VELKOST_PLOCHY || y < 0 || y >= VELKOST_PLOCHY) {
//         return NULL;
//     }
//     return &hraciaPlocha->hraciaPlocha[x][y];
// }
//
// void vypis(HraciaPlocha* hraciaPlocha) {
//     for (int i = 0; i < VELKOST_PLOCHY; i++) {
//         for (int j = 0; j < VELKOST_PLOCHY; j++) {
//             // Priamo vypíše znak reprezentovaný enumom TypPolickaEnum
//             printf("%c ", hraciaPlocha->hraciaPlocha[i][j].typPolicka);
//         }
//         printf("\n");
//     }
// }

void destroy_hraciaPlocha(HraciaPlocha* hraciaPlocha)
{
    for (int i = 0; i < VELKOST_PLOCHY; i++)
    {
        free(hraciaPlocha->hraciaPlocha[i]);
        hraciaPlocha->hraciaPlocha[i] = NULL;
    }
    free(hraciaPlocha->hraciaPlocha);
    hraciaPlocha->hraciaPlocha = NULL;
}






