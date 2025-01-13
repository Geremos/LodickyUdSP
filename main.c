#include <stdio.h>

// Entry point of the program
#include "GUI.h"
#include "HraciaPlocha.h"
GtkWidget *buttons[VELKOST_PLOCHY][VELKOST_PLOCHY];

void initialize_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    if (!gtk_css_provider_load_from_path(provider, "../Grafika/Style.css", NULL)) {
        g_warning("CSS file not found or has errors");
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    initialize_css();
    // Inicializácia herných plôch
    HraciaPlocha hracova_plocha;
    HraciaPlocha oponentova_plocha;
    init_hraciaPlocha(&hracova_plocha);
    init_hraciaPlocha(&oponentova_plocha);

    open_ship_editor(&hracova_plocha);

    // Vytvorenie hlavného GUI rozloženia
    create_main_layout(&hracova_plocha, &oponentova_plocha);

    // Spustenie hlavnej slučky GTK
    gtk_main();

    // Uvoľnenie pamäte herných plôch
    destroy_hraciaPlocha(&hracova_plocha);
    destroy_hraciaPlocha(&oponentova_plocha);


    return 0;
}

