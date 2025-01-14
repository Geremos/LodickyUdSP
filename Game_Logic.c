//
// Created by juraj on 13. 1. 2025.
//
#include "game_logic.h"
#include <stdbool.h>
#include "GUI.h"

void initialize_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    if (!gtk_css_provider_load_from_path(provider, "../Grafika/Style.css", NULL)) {
        g_warning("CSS file not found or has errors");
    }
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
}
void initialize_game_state(GameState *state, char* player_name) {
    // Inicializácia hráčskej a súperovej plochy
    Hrac* hrac = malloc(sizeof(Hrac));
    Hrac* opponent = malloc(sizeof(Hrac));
    initialize_player(hrac, player_name);
    initialize_player(opponent, "Oponent");

    state->hrac = *hrac;
    state->opponent = *opponent;

    state->hrac_score = 0;
    state->opponent_score = 0;
    state->game_over = false;

    initialize_css();


    open_ship_editor(state->hrac.plocha); // Editor lodičiek pre hráča

    // Vytvorenie hlavného GUI rozloženia
    create_main_layout(state->hrac.plocha, state->opponent.plocha);

    // Spustenie hlavnej slučky GTK
    gtk_main();

    // Uvoľnenie zdrojov
    destroy_player(hrac);
    destroy_player(opponent);
}

bool is_game_over(GameState *state) {
    // Logika na kontrolu konca hry (napr. zničené všetky lode)
    return state->game_over;
}

// Globálne premenné na uloženie kliknutých súradníc
static int first_click_x = -1;
static int first_click_y = -1;

// Funkcia na spracovanie kliknutí pri nastavovaní lodičky
void handle_ship_placement(GtkWidget *widget, gpointer data) {
    Policko *policko = (Policko *)data;

    if (first_click_x == -1 && first_click_y == -1) {
        // Prvé kliknutie
        first_click_x = policko->x;
        first_click_y = policko->y;
        g_print("Prvé kliknutie: (%d, %d)\n", first_click_x, first_click_y);
    } else {
        // Druhé kliknutie
        int second_click_x = policko->x;
        int second_click_y = policko->y;
        g_print("Druhé kliknutie: (%d, %d)\n", second_click_x, second_click_y);

        // Kontrola, či sú na rovnakom riadku alebo stĺpci
        if (first_click_x != second_click_x && first_click_y != second_click_y) {
            g_print("Lodička musí byť umiestnená horizontálne alebo vertikálne!\n");
            first_click_x = -1;
            first_click_y = -1;
            return;
        }

        // Výpočet dĺžky lodičky
        int length = (first_click_x == second_click_x)
                         ? abs(second_click_y - first_click_y) + 1
                         : abs(second_click_x - first_click_x) + 1;

        // Overenie, či je počet lodí daného typu k dispozícii
        enum LodickaEnum typLodicky = length;
        Hrac *hrac = get_player();           // Získanie aktuálneho hráča (implementácia závisí od logiky hry)

        if (hrac->lode[typLodicky - 1] <= 0) {
            g_print("Nie je dostupná loď tejto veľkosti (%d)!\n", length);
            first_click_x = -1;
            first_click_y = -1;
            return;
        }

        // Nastavenie lodičky na hracej ploche
        if (nastavLodicku(typLodicky,
                          MIN(first_click_x, second_click_x),
                          MIN(first_click_y, second_click_y),
                          MAX(first_click_x, second_click_x),
                          MAX(first_click_y, second_click_y),
                          hrac)) {
            g_print("Lodička úspešne umiestnená!\n");
            hrac->lode[typLodicky - 1]--; // Zníženie dostupného počtu lodí tohto typu

            // Aktualizácia GUI
            update_grid(); // Táto funkcia by mala byť definovaná v GUI na prekreslenie mriežky
        } else {
            g_print("Chyba pri nastavovaní lodičky!\n");
        }

        // Reset kliknutí
        first_click_x = -1;
        first_click_y = -1;
    }
}
