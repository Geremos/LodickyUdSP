//
// Created by juraj on 13. 1. 2025.
//
#ifndef GUI_H
#define GUI_H
// Inicializácia GUI
#include <gtk/gtk.h>
#include "HraciaPlocha.h"
#include "Hrac.h"

typedef struct  Gui_Click_Data
{
    Hrac *hrac;
    int x;
    int y;
} Gui_Click_Data;

// Vytvára hlavné rozloženie GUI
void create_main_layout(Hrac* hrac, Hrac *oponent);
void create_grid(GtkWidget *grid, Hrac* hrac, bool is_interactive, GCallback callback);
void strela(GtkWidget *widget, gpointer data);
void suradnica_lodicky(GtkWidget *widget, gpointer data);
void on_confirm_clicked(GtkWidget *widget, gpointer data);
void open_ship_editor(Hrac *hrac);
void create_editor_grid(GtkWidget *grid, Hrac *hrac);
void handle_ship_placement(GtkWidget *widget, gpointer data);
void place_ship_on_grid(GtkWidget *grid, int start_x, int start_y, int end_x, int end_y);
#endif // GUI_H
