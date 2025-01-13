//
// Created by juraj on 12. 1. 2025.
//

#ifndef HRACIAPLOCHA_H
#define HRACIAPLOCHA_H
#include "Policko.h"
#include <gtk-3.0/gtk/gtk.h>
# define  VELKOST_PLOCHY  10

typedef struct HraciaPlocha
{
    Policko** hraciaPlocha;
} HraciaPlocha;

void init_hraciaPlocha(HraciaPlocha* hraciaPlocha);
Policko* getPolicko(int x, int y, HraciaPlocha* hraciaPlocha);
void vypis(HraciaPlocha* hraciaPlocha);
bool nastavLodicku(enum LodickaEnum typLodicky,int zX,int zY,int kX,int kY, HraciaPlocha* hraciaPlocha);
//void nastavBorder(int zX, int zY, int kX, int kY);
//void create_grid(GtkWidget *grid, HraciaPlocha *hraciaPlocha);
//bool on_button_clicked(GtkWidget *widget, gpointer data);
void destroy_hraciaPlocha(HraciaPlocha* hraciaPlocha);
#endif //HRACIAPLOCHA_H
