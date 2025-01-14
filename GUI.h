//
// Created by juraj on 13. 1. 2025.
//
#ifndef GUI_H
#define GUI_H
// Inicializácia GUI
#include <gtk/gtk.h>
#include "HraciaPlocha.h"

// Vytvára hlavné rozloženie GUI
void create_main_layout(HraciaPlocha *hrac, HraciaPlocha *oponent);
void create_grid(GtkWidget *grid, HraciaPlocha *plocha, bool is_interactive, GCallback callback);
void strela(GtkWidget *widget, gpointer data);
void suradnica_lodicky(GtkWidget *widget, gpointer data);
void on_confirm_clicked(GtkWidget *widget, gpointer data);
void open_ship_editor(HraciaPlocha *plocha);
void create_editor_grid(GtkWidget *grid, HraciaPlocha *plocha);

#endif // GUI_H
