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
    g_object_unref(provider);
}
void initialize_game_state(GameState *state, char* player_name) {
    if (!state) {
        g_warning("GameState nie je inicializovaný!");
        return;
    }
    // Inicializácia hráčskej a súperovej plochy
    Hrac* hrac = malloc(sizeof(Hrac));
    Hrac* opponent = malloc(sizeof(Hrac));
    init_player(hrac, player_name);
    init_player(opponent, "Oponent");

    state->hrac = hrac;
    state->opponent = opponent;

    state->hrac_score = 0;
    state->opponent_score = 0;
    state->game_over = false;

    initialize_css();

    open_ship_editor(state->hrac); // Editor lodičiek pre hráča

    // Vytvorenie hlavného GUI rozloženia
    create_main_layout(state->hrac, state->opponent);

    // Spustenie hlavnej slučky GTK
    gtk_main();

    // Uvoľnenie zdrojov
    destroy_player(hrac);
    destroy_player(opponent);
    free(hrac);
    free(opponent);
}

bool is_game_over(GameState *state) {
    // Logika na kontrolu konca hry (napr. zničené všetky lode)
    return state->game_over;
}




