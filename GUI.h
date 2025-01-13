//
// Created by juraj on 13. 1. 2025.
//
#ifndef GUI_H
#define GUI_H
// Inicializácia GUI
#include <gtk/gtk.h>
#include "HraciaPlocha.h"
#include "Game_Logic.h"

// Vytvára hlavné rozloženie GUI
void create_main_layout(HraciaPlocha *hrac, HraciaPlocha *oponent);

#endif // GUI_H
