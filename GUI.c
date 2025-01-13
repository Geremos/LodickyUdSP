#include "gui.h"
#include "game_logic.h"

static GtkWidget *oponentovaPlochaGrid;
static GtkWidget *hracovaPlochaGrid;
static GtkWidget *infoBox; // Stredný panel so skóre a informáciami

void create_grid(GtkWidget *grid, HraciaPlocha *plocha) {
    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            GtkWidget *button = gtk_button_new();
            gtk_widget_set_size_request(button, 60, 60);

            // Nastavenie obrázku podľa obsahu políčka
            GtkWidget *image;
            if (plocha->hraciaPlocha[i][j].lodickaEnum != noShip) {
                image = gtk_image_new_from_file("../GUI_res/lodicka.png");
            } else {
                image = gtk_image_new_from_file("../GUI_res/voda.png");
            }

            gtk_button_set_image(GTK_BUTTON(button), image);

            // Pripojenie signálu pre kliknutie na tlačidlo
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), &plocha->hraciaPlocha[i][j]);

            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
        }
    }
}

void create_main_layout(HraciaPlocha *hrac, HraciaPlocha *oponent) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Battleships");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), mainGrid);

    // Oponentova hracia plocha (vľavo)
    oponentovaPlochaGrid = gtk_grid_new();
    create_grid(oponentovaPlochaGrid, oponent);
    gtk_grid_attach(GTK_GRID(mainGrid), oponentovaPlochaGrid, 0, 0, 1, 1);

    // Stredný panel (info o skóre, správy, stav hry)
    infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new("Zobrazovanie skóre a stavu hry");
    gtk_box_pack_start(GTK_BOX(infoBox), label, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(mainGrid), infoBox, 1, 0, 1, 1);

    // Hracova hracia plocha (vpravo)
    hracovaPlochaGrid = gtk_grid_new();
    create_grid(hracovaPlochaGrid, hrac);
    gtk_grid_attach(GTK_GRID(mainGrid), hracovaPlochaGrid, 2, 0, 1, 1);

    gtk_widget_show_all(window);
}
