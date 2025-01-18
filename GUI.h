//
// Created by juraj on 13. 1. 2025.
//
#ifndef GUI_H
#define GUI_H
// Inicializácia GUI
#include <gtk/gtk.h>
#include "Hrac.h"

// Štruktúra na uchovanie stavu GUI
typedef struct GuiContext {
    GtkWidget *main_window;
    GtkWidget *oponentovaPlochaGrid;
    GtkWidget *hracovaPlochaGrid;
    GtkWidget *infoBox;
    GtkWidget *editor_grid;
    GtkWidget *confirm_button;
    Hrac *hrac;
    Hrac *oponent;
    int x;
    int y;
    int first_click_x;
    int first_click_y;
} GuiContext;

typedef struct  Gui_Click_data {
    int x;
    int y;
    Hrac *hrac;
    GtkWidget* grid;
} Gui_Click_data;

// Vytvára hlavné rozloženie GUI
GuiContext* create_gui_context(Hrac *hrac, Hrac *oponent);
void destroy_gui_context(GuiContext *gui);

//hra
void create_main_layout(GuiContext* gui);

// Vytvorenie hracej plochy
void create_grid(GuiContext* gui, bool is_interactive, GCallback callback, bool is_oponent);

void strela(GtkWidget *widget, gpointer data);
void on_editor_window_close(GtkWidget *widget, GdkEvent *event, gpointer data);
void suradnica_lodicky(GtkWidget *widget, gpointer data);
void on_confirm_clicked(GtkWidget *widget, gpointer data);
void open_ship_editor(GuiContext *gui);
void create_editor_grid(GtkWidget *grid, Hrac *hrac);
void handle_ship_placement(GtkWidget *widget, gpointer data);
void place_ship_on_grid(GtkWidget *grid, int start_x, int start_y, int end_x, int end_y);
bool are_all_ships_done(Hrac* hrac);
void create_main_window(GuiContext* gui);
void on_start_game_clicked(GtkWidget *widget, gpointer data);

#endif // GUI_H
