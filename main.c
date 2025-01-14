#include <stdio.h>

// Entry point of the program
#include "Game_Logic.h"

void initialize_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    if (!gtk_css_provider_load_from_path(provider, "../Grafika/Style.css", NULL)) {
        g_warning("CSS file not found or has errors");
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {
    GameState state;
    initialize_game_state(&state);

    gtk_init(&argc, &argv);
    return 0;
}


/*

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

// Funkcia na prekrytie obrázkov
GtkWidget *overlay_images(const char *base_image_path, const char *overlay_image_path) {
    // Načítanie základného obrázka (voda)
    GdkPixbuf *base_pixbuf = gdk_pixbuf_new_from_file(base_image_path, NULL);
    if (!base_pixbuf) {
        g_print("Chyba pri načítaní základného obrázka!\n");
        return NULL;
    }

    // Načítanie prekrývajúceho obrázka (loď)
    GdkPixbuf *overlay_pixbuf = gdk_pixbuf_new_from_file(overlay_image_path, NULL);
    if (!overlay_pixbuf) {
        g_print("Chyba pri načítaní prekrývajúceho obrázka!\n");
        g_object_unref(base_pixbuf);
        return NULL;
    }

    // Skopírovanie základného obrázka (voda) na nový pixbuf
    GdkPixbuf *result_pixbuf = gdk_pixbuf_copy(base_pixbuf);

    // Prekrytie obrázka lode na vodu
    gdk_pixbuf_composite(
        overlay_pixbuf,          // Zdrojový obrázok (loď)
        result_pixbuf,           // Cieľový obrázok (kombinácia)
        0, 0,                    // Začiatok kreslenia na cieľovom pixbufe
        gdk_pixbuf_get_width(overlay_pixbuf),  // Šírka prekrytia
        gdk_pixbuf_get_height(overlay_pixbuf), // Výška prekrytia
        0, 0,                    // Posun (offset) v rámci cieľového pixbufu
        1.0, 1.0,                // Faktor zväčšenia (scale factors)
        GDK_INTERP_BILINEAR,            // Interpolácia pre kvalitu kreslenia
        255
    );

    // Uvoľnenie pôvodných pixbufov
    g_object_unref(base_pixbuf);
    g_object_unref(overlay_pixbuf);

    // Vytvorenie GtkImage z výsledného pixbufu
    GtkWidget *result_image = gtk_image_new_from_pixbuf(result_pixbuf);

    // Uvoľnenie výsledného pixbufu (keďže je už použitý v GtkImage)
    g_object_unref(result_pixbuf);

    return result_image;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Vytvorenie hlavného okna
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kombinácia obrázkov");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Tlačidlo s kombinovaným obrázkom
    GtkWidget *button = gtk_button_new();
    GtkWidget *combined_image = overlay_images("../Grafika/Background.png", "../Grafika/Lodicka4_V.png");
    if (combined_image) {
        gtk_button_set_image(GTK_BUTTON(button), combined_image);
    }

    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}*/















