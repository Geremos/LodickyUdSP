//
// Created by juraj on 12. 1. 2025.
//

#include "Policko.h"

#include <stdlib.h>

void init_Policko(Policko* policko, int x, int y)
{

    policko->x = x;
    policko->y = y;
    policko->strela = false;
    policko->typPolicka = voda;
    policko->lodickaEnum = noShip;

}

int getX(Policko* policko)
{
    return policko->x;
}

int getY(Policko* policko)
{
    return policko->y;
}

bool getStrela(Policko* policko)
{
    return policko->strela;
}

void setStrela(Policko* policko)
{
    policko->strela = true;
}

enum TypPolickaEnum getTyp(Policko* policko)
{
    return policko->typPolicka;
}

void setTypPolicka(enum TypPolickaEnum value, Policko* policko)
{
    policko->typPolicka = value;
}

void setLodicka(enum LodickaEnum value, Policko* policko)
{
    policko->lodickaEnum = value;
}

enum LodickaEnum getLodickaEnum(Policko* policko)
{
    return policko->lodickaEnum;
}

void destroy_Policko(Policko* policko)
{
    free(policko);
}