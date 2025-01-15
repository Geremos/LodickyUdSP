//
// Created by juraj on 12. 1. 2025.
//
#ifndef POLICKO_H
#define POLICKO_H

#include <stdbool.h>
#include "TypPolickaEnum.h"

typedef struct Policko
{
    enum TypPolickaEnum typPolicka;
    enum LodickaEnum lodickaEnum;
    int poradieVlodi;
    bool spracovane;
    bool strela;
    int x;
    int y;
} Policko;


void init_Policko(Policko* policko, int x, int y);
int getX(Policko* policko);
int getY(Policko* policko);
bool getStrela(Policko* policko);
void setStrela(Policko* policko);
enum TypPolickaEnum getTyp(Policko* policko);
void setTypPolicka(enum TypPolickaEnum value, Policko* policko);
void setLodicka(enum LodickaEnum value, Policko* policko);
enum LodickaEnum getLodickaEnum(Policko* policko);
void destroy_policko(Policko* policko);


#endif //POLICKO_H
