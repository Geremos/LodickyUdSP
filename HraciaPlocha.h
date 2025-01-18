//
// Created by juraj on 13. 1. 2025.
//


//
// Created by juraj on 12. 1. 2025.
//

#ifndef HRACIAPLOCHA_H
#define HRACIAPLOCHA_H
#include "Policko.h"
#include "GenericMatrix.h"

# define  VELKOST_PLOCHY  10

typedef struct HraciaPlocha
{
    GenericMatrix* hraciaPlocha;
} HraciaPlocha;

void init_hraciaPlocha(HraciaPlocha* hraciaPlocha);
void destroy_hraciaPlocha(HraciaPlocha* hraciaPlocha);

const Policko* getPolicko(int x, int y, HraciaPlocha* hraciaPlocha);
void setTypPolickaNaPloche(enum TypPolickaEnum typ, int x, int y, HraciaPlocha* hraciaPlocha);
#endif //HRACIAPLOCHA_H
