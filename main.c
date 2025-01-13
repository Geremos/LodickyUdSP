#include <stdio.h>

// Entry point of the program
#include "HraciaPlocha.h"
GtkWidget *buttons[VELKOST_PLOCHY][VELKOST_PLOCHY];
#include <glib.h> // Potrebné pre g_get_current_dir()

// Callback funkcia pre kliknutie na tlačidlo
/*
void on_button_clicked(GtkWidget *widget, gpointer data) {
    int *pos = (int *)data;
    int x = pos[0];
    int y = pos[1];

    g_print("Kliknuté na políčko: (%d, %d)\n", x, y);

    GtkWidget *new_image = gtk_image_new_from_file("hit.png");
    gtk_button_set_image(GTK_BUTTON(widget), new_image);

    free(pos);
}


// Inicializácia GUI
void create_grid(GtkWidget *grid) {
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 0);

    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            buttons[i][j] = gtk_button_new();
            GtkWidget *image = gtk_image_new_from_file("water.png");
            gtk_button_set_image(GTK_BUTTON(buttons[i][j]), image);
            gtk_button_set_always_show_image(GTK_BUTTON(buttons[i][j]), TRUE);
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j, i, 1, 1);

            int *pos = malloc(2 * sizeof(int));
            pos[0] = i;
            pos[1] = j;

            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(on_button_clicked), pos);
        }
    }
}
*/

/*void on_button_clicked(GtkWidget *widget, gpointer data) {
    int *pos = (int *)data;
    int x = pos[0];
    int y = pos[1];

    g_print("Kliknuté na políčko: (%d, %d)\n", x, y);

    // Overenie, či tlačidlo už má obrázok (napr. výbuch)
    GtkWidget *current_image = gtk_button_get_image(GTK_BUTTON(widget));
    if (current_image == NULL) {
        GtkWidget *image = gtk_image_new_from_file("explosion.png");
        gtk_button_set_image(GTK_BUTTON(widget), image);
    } else {
        g_print("Tlačidlo už bolo kliknuté.\n");
    }

    // free(pos);  // Uvoľnenie pamäte, ak bola alokovaná
}

void create_grid(GtkWidget *grid) {
    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            buttons[i][j] = gtk_button_new();
            gtk_widget_set_size_request(buttons[i][j], 60, 60);
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j, i, 1, 1);

            // Click event
            int *pos = malloc(2 * sizeof(int));
            pos[0] = i;
            pos[1] = j;
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(on_button_clicked), pos);
        }
    }
}
*/
// Hlavná funkcia
int main(int argc, char *argv[]) {

    // gtk_init(&argc, &argv);
    //
    // GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // gtk_window_set_title(GTK_WINDOW(window), "Battleships");
    // gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    // g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //
    // // Aplikácia CSS
    // GtkCssProvider *provider = gtk_css_provider_new();
    // gtk_css_provider_load_from_path(provider, "../GUI_res/Button.css", NULL);
    // GdkScreen *screen = gdk_screen_get_default();
    // gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    //
    // // Vytvorenie overlay a mriežky
    // GtkWidget *overlay = gtk_overlay_new();
    // gtk_container_add(GTK_CONTAINER(window), overlay);
    //
    // GtkWidget *background = gtk_image_new_from_file("background.png");
    // gtk_overlay_add_overlay(GTK_OVERLAY(overlay), background);
    //
    // GtkWidget *grid = gtk_grid_new();
    // gtk_overlay_add_overlay(GTK_OVERLAY(overlay), grid);
    //
    // create_grid(grid);
    //
    // gtk_widget_show_all(window);
    // gtk_main();
/*
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hracia Plocha");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    HraciaPlocha hraciaPlocha;
    init_hraciaPlocha(&hraciaPlocha);
    create_grid(grid, &hraciaPlocha);

    gtk_widget_show_all(window);
    gtk_main();

    destroy_hraciaPlocha(&hraciaPlocha);*/



    return 0;
}