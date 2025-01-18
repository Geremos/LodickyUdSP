//
// Created by juraj on 13. 1. 2025.
//
#include "GUI.h"

GuiContext* create_gui_context(Hrac *hrac, Hrac *oponent) {
    GuiContext *gui = malloc(sizeof(GuiContext));
    if (!gui) return NULL;

    gui->main_window = NULL;
    gui->oponentovaPlochaGrid = NULL;
    gui->hracovaPlochaGrid = NULL;
    gui->infoBox = NULL;
    gui->editor_grid = NULL;
    gui->confirm_button = NULL;
    gui->hrac = hrac;
    gui->oponent = oponent;
    gui->x = -1;
    gui->y = -1;
    gui->first_click_x = -1;
    gui->first_click_y = -1;
    return gui;
}

void destroy_gui_context(GuiContext *gui) {
    free(gui);
}

void strela(GtkWidget *widget, gpointer data) {
    // Získanie ukazovateľa na konkrétne políčko
    Gui_Click_data *click_data = (Gui_Click_data*)data;
    Hrac *hrac = click_data->hrac;
    int x = click_data->x;
    int y = click_data->y;
     Policko *policko = getPolicko(x,y, getHraciaPlocha(hrac));

    g_print("Kliknuté na políčko: (%d, %d)\n", x, y);

    // Kontrola, či už bolo na políčko vystrelené
    if (getStrela(policko)) {
        g_print("Na toto políčko už bolo vystrelené.\n");
        return;
    }

    // Načítanie pôvodného obrázka z tlačidla
    GtkWidget *current_image = gtk_button_get_image(GTK_BUTTON(widget));
    if (!current_image) {
        g_print("Chyba: Tlačidlo nemá obrázok.\n");
        return;
    }

    GdkPixbuf *current_pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(current_image));
    if (!current_pixbuf) {
        g_print("Chyba: Nepodarilo sa načítať pôvodný obrázok tlačidla.\n");
        return;
    }
    const char *image_path = "";
    // Načítanie obrázka strely
    if (getTyp(policko) == lodicka) {
        g_print("Trafená loď!\n");
        image_path = "../Grafika/Trefa.png";
    } else {
        g_print("Voda!\n");
        image_path = "../Grafika/clup.png";
    }

    GdkPixbuf *shot_pixbuf = gdk_pixbuf_new_from_file(image_path, NULL);
    if (!shot_pixbuf) {
        g_print("Chyba: Nepodarilo sa načítať obrázok strely.\n");
        return;
    }

    // Kombinácia pôvodného obrázka a obrázka strely
    GdkPixbuf *combined_pixbuf = gdk_pixbuf_copy(current_pixbuf);
    gdk_pixbuf_composite(
        shot_pixbuf,               // Zdrojový pixbuf (strela)
        combined_pixbuf,           // Cieľový pixbuf (existujúci obrázok)
        0, 0,                      // Začiatok cieľového pixbufu
        gdk_pixbuf_get_width(shot_pixbuf), gdk_pixbuf_get_height(shot_pixbuf), // Rozmery strely
        0, 0,                      // Posun
        1.0, 1.0,                  // Mierka (1:1)
        GDK_INTERP_BILINEAR,       // Interpolácia
        255                        // Priehľadnosť (255 = nepriehľadné)
    );

    // Nastavenie kombinovaného obrázka späť na tlačidlo
    GtkWidget *new_image = gtk_image_new_from_pixbuf(combined_pixbuf);
    gtk_button_set_image(GTK_BUTTON(widget), new_image);

    // Uvoľnenie zdrojov
    g_object_unref(combined_pixbuf);
    g_object_unref(shot_pixbuf);

    // Nastavenie stavu políčka, ako zasiahnutého
    setStrela(policko);
}


void create_grid(GuiContext* gui, bool is_interactive, GCallback callback, bool is_oponent, bool is_editor) {
    GtkWidget *grid;
    if (is_oponent) {
        gui->oponentovaPlochaGrid = gtk_grid_new();
        grid = gui->oponentovaPlochaGrid;
    } else {
        gui->hracovaPlochaGrid = gtk_grid_new();
        grid = gui->hracovaPlochaGrid;
    }

    // Pridanie súradníc, ako hlavičky
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            if (i == 0 && j == 0) {
                // Prázdny roh
                GtkWidget *empty_label = gtk_label_new("");
                gtk_grid_attach(GTK_GRID(grid), empty_label, j, i, 1, 1);
            } else if (i == 0) {
                // Čísla hore (1, 2, 3, ...)
                char *text = g_strdup_printf("%d", j);
                GtkWidget *label = gtk_label_new(text);
                g_free(text); // Uvoľníme pamäť po použití
                // Pridanie CSS triedy
                gtk_widget_set_name(label, "coordinate-label");
                gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1);
            } else if (j == 0) {
                // Písmená na boku (A, B, C, ...)
                char *text = g_strdup_printf("%c", 'A' + i - 1);
                GtkWidget *label = gtk_label_new(text);
                g_free(text);
                // Pridanie CSS triedy
                gtk_widget_set_name(label, "coordinate-label");
                gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1);
            } else {
                // Tlačidlo pre mriežku
                GtkWidget *button = gtk_button_new();
                gtk_widget_set_size_request(button, 60, 60);

                // Nastavenie obrázku podľa obsahu políčka
                GdkPixbuf *original_pixbuf = gdk_pixbuf_new_from_file("../Grafika/Background.png", NULL);
                GdkPixbuf *sub_pixbuf = gdk_pixbuf_new_subpixbuf(
                    original_pixbuf,
                    (j - 1) * 60, (i - 1) * 60, // Orezanie časti obrázka
                    60, 60
                );
                GtkWidget *image = gtk_image_new_from_pixbuf(sub_pixbuf);
                gtk_button_set_image(GTK_BUTTON(button), image);
                gtk_widget_set_name(button, "plocha");

                if (is_interactive && callback != NULL) {
                    // Dynamicky alokujeme štruktúru `Gui_Click_Data` pre tlačidlo

                    Gui_Click_data *data = malloc(sizeof(Gui_Click_data));
                    if (!data) {
                        g_print("Chyba: Nepodarilo sa alokovať pamäť pre `Gui_Click_Data`.\n");return;
                    }
                    if (is_oponent) {
                        data->hrac = gui->oponent;
                        data->grid = gui->oponentovaPlochaGrid;
                    } else
                    {
                        data->hrac = gui->hrac;
                        data->grid = gui->hracovaPlochaGrid;
                    }
                    data->x = i - 1;
                    data->y = j - 1;
                    data->gui = gui;
                    g_signal_connect_data(button, "clicked", callback, data, (GClosureNotify)free, 0);
                }

                gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);

                // Uvoľnenie zdrojov
                g_object_unref(sub_pixbuf);
                g_object_unref(original_pixbuf);
            }
        }
    }
}

void on_editor_window_close(GtkWidget *widget, GdkEvent *event, gpointer data) {
    GuiContext *gui =(GuiContext*)data;
    if (!are_all_ships_done(gui->hrac)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
                                                   "Nemôžete zatvoriť editor, kým nerozložíte všetky lodičky!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        gtk_widget_destroy(widget);
    }
}

void place_ship_on_grid(GtkWidget *grid, int start_x, int start_y, int end_x, int end_y) {
    // Určenie, či je lodička horizontálna alebo vertikálna
    bool is_horizontal = (start_x == end_x);
    int length = is_horizontal ? abs(end_y - start_y) + 1 : abs(end_x - start_x) + 1;
    const char *ship_image_path = NULL;

    // Výber správneho obrázka lodičky
    switch (length) {
        case 2:
            ship_image_path = is_horizontal ? "../Grafika/lodicka2_H.png" : "../Grafika/lodicka2_V.png";
            break;
        case 3:
            ship_image_path = is_horizontal ? "../Grafika/lodicka3_H.png" : "../Grafika/lodicka3_V.png";
            break;
        case 4:
            ship_image_path = is_horizontal ? "../Grafika/lodicka4_H.png" : "../Grafika/lodicka4_V.png";
            break;
        case 5:
            ship_image_path = is_horizontal ? "../Grafika/lodicka5_H.png" : "../Grafika/lodicka5_V.png";
            break;
        default:
            g_print("Neplatná dĺžka lodičky: %d\n", length);
            return;
    }

    // Načítanie obrázka lodičky
    GdkPixbuf *ship_pixbuf = gdk_pixbuf_new_from_file(ship_image_path, NULL);
    if (!ship_pixbuf) {
        g_print("Chyba: Nepodarilo sa načítať obrázok lodičky.\n");
        return;
    }

    // Rozdelenie obrázka lodičky na časti a kombinácia s existujúcim obrázkom tlačidla

    for (int i = 0; i < length; i++) {
        int pos_x = is_horizontal ? start_x : start_x + i;
        int pos_y = is_horizontal ? start_y + i : start_y;

        // Orezanie časti obrázka lodičky
        int crop_x = is_horizontal ? (i * gdk_pixbuf_get_width(ship_pixbuf) / length) : 0;
        int crop_y = is_horizontal ? 0 : (i * gdk_pixbuf_get_height(ship_pixbuf) / length);
        int crop_width = is_horizontal ? (gdk_pixbuf_get_width(ship_pixbuf) / length) : gdk_pixbuf_get_width(ship_pixbuf);
        int crop_height = is_horizontal ? gdk_pixbuf_get_height(ship_pixbuf) : (gdk_pixbuf_get_height(ship_pixbuf) / length);

        GdkPixbuf *ship_part_pixbuf = gdk_pixbuf_new_subpixbuf(ship_pixbuf, crop_x, crop_y, crop_width, crop_height);

        // Nájdeme tlačidlo v mriežke
        GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(grid), pos_y + 1, pos_x + 1); // +1 kvôli hlavičke
        if (button) {
            // Získanie pôvodného obrázka tlačidla
            GtkWidget *current_image = gtk_button_get_image(GTK_BUTTON(button));
            if (!current_image) {
                g_print("Chyba: Tlačidlo nemá obrázok.\n");
                g_object_unref(ship_part_pixbuf);
                continue;
            }

            GdkPixbuf *current_pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(current_image));
            if (!current_pixbuf) {
                g_print("Chyba: Nepodarilo sa načítať pôvodný obrázok tlačidla.\n");
                g_object_unref(ship_part_pixbuf);
                continue;
            }

            // Vytvorenie kombinovaného obrázka
            GdkPixbuf *combined_pixbuf = gdk_pixbuf_copy(current_pixbuf);
            gdk_pixbuf_composite(
                ship_part_pixbuf,              // Zdrojový pixbuf (časť lodičky)
                combined_pixbuf,               // Cieľový pixbuf (existujúci obrázok)
                0, 0,                          // Začiatok cieľového pixbufu
                crop_width, crop_height,       // Rozmery orezania
                0, 0,                          // Posun
                1.0, 1.0,                      // Mierka (1:1)
                GDK_INTERP_BILINEAR,           // Interpolácia
                255                            // Priehľadnosť (255 = nepriehľadné)
            );

            // Nastavenie nového obrázka na tlačidlo
            GtkWidget *image = gtk_image_new_from_pixbuf(combined_pixbuf);
            gtk_button_set_image(GTK_BUTTON(button), image);

            // Uvoľnenie zdrojov
            g_object_unref(combined_pixbuf);
        }

        g_object_unref(ship_part_pixbuf);
    }

    g_object_unref(ship_pixbuf);
}

void create_main_layout(GuiContext* gui) {
     gui->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gui->main_window), "Battleships");
    gtk_window_set_default_size(GTK_WINDOW(gui->main_window), 1200, 600);
    g_signal_connect(gui->main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *mainGrid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(gui->main_window), mainGrid);


    create_grid(gui, true, G_CALLBACK(strela),true,false);
    gtk_grid_attach(GTK_GRID(mainGrid), gui->oponentovaPlochaGrid, 0, 0, 1, 1);

    // Stredný panel (info o skóre, správy, stav hry)
    gui->infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new("Zobrazovanie skóre a stavu hry");
    gtk_box_pack_start(GTK_BOX(gui->infoBox), label, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(mainGrid), gui->infoBox, 1, 0, 1, 1);

    create_grid(gui, false, NULL,false,false);
    gtk_grid_attach(GTK_GRID(mainGrid), gui->hracovaPlochaGrid, 2, 0, 1, 1);

    // Prechádzame cez hraciu plochu hráča
    int start_x = -1;
    int start_y = -1;
    int end_x = -1;
    int end_y = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i+1; j++) {
            start_x = gui->hrac->lode[i][j].start_x;
            start_y = gui->hrac->lode[i][j].start_y;
            end_x = gui->hrac->lode[i][j].end_x;
            end_y = gui->hrac->lode[i][j].end_y;
            place_ship_on_grid(gui->hracovaPlochaGrid, start_x, start_y, end_x, end_y);
        }
    }

    gtk_widget_show_all(gui->main_window);
}


void on_confirm_clicked(GtkWidget *widget, gpointer data) {
    GuiContext *gui = (GuiContext *)data;

    // Kontrola, či hráč rozložil všetky lodičky
    if (!are_all_ships_done(gui->hrac)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
                                                   "Nemôžete potvrdiť, kým nerozložíte všetky lodičky!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return; // Zabráni zatvoreniu editoru
    }

    // Zavretie editorového okna
    GtkWidget *editor_window = GTK_WIDGET(gtk_widget_get_toplevel(widget));
    gtk_widget_destroy(editor_window); // Zničí okno editoru

    g_print("Lodičky hráča boli potvrdené a editor zatvorený.\n");
    create_main_layout(gui);
}


// Funkcia na spracovanie kliknutí pri nastavovaní lodičky
void handle_ship_placement(GtkWidget *widget, gpointer data) {
    Gui_Click_data *click_data = (Gui_Click_data*)data;
    GuiContext *gui = click_data->gui;
    if (gui->first_click_x == -1 && gui->first_click_y == -1) {
        gui->first_click_x = click_data->x;
        gui->first_click_y = click_data->y;
        g_print("Prvé kliknutie: (%d, %d)\n", gui->first_click_x, gui->first_click_y);
    } else {
        // Druhé kliknutie
        int second_click_x = click_data->x;
        int second_click_y = click_data->y;
        g_print("Druhé kliknutie: (%d, %d)\n", second_click_x, second_click_y);

        // Kontrola, či sú na rovnakom riadku alebo stĺpci
        if (gui->first_click_x != second_click_x && gui->first_click_y != second_click_y) {
            g_print("Lodička musí byť umiestnená horizontálne alebo vertikálne!\n");
            gui->first_click_x = -1;
            gui->first_click_y = -1;
            return;
        }

        if (gui->first_click_x == second_click_x && gui->first_click_y == second_click_y) {
            g_print("Lodička musí mať dĺžku aspoň 2 políčka!\n");
            gui->first_click_x = -1;
            gui->first_click_y = -1;
            return;
        }

        // Výpočet dĺžky lodičky
        int length = (gui->first_click_x == second_click_x)
                         ? abs(second_click_y - gui->first_click_y) + 1
                         : abs(second_click_x - gui->first_click_x) + 1;

        // Overenie, či je počet lodí daného typu k dispozícii
        enum LodickaEnum typLodicky = length;

        if (click_data->hrac->lode[typLodicky - 2] == 0) {
            g_print("Nie je dostupná loď tejto veľkosti (%d)!\n", length);
            gui->first_click_x = -1;
            gui->first_click_y = -1;
            return;
        }

        int begin_x = MIN(gui->first_click_x, second_click_x);
        int begin_y = MIN(gui->first_click_y, second_click_y);
        int end_x = MAX(gui->first_click_x, second_click_x);
        int end_y = MAX(gui->first_click_y, second_click_y);
        // Nastavenie lodičky na hracej ploche
        if (nastavLodicku(typLodicky, begin_x, begin_y, end_x, end_y, click_data->hrac)) {
            g_print("Lodička úspešne umiestnená!\n");

            // Aktualizácia GUI
            place_ship_on_grid(gui->hracovaPlochaGrid, begin_x, begin_y, end_x, end_y);
        } else {
            g_print("Chyba pri nastavovaní lodičky!\n");
        }

        // Reset kliknutí
        gui->first_click_x = -1;
        gui->first_click_y = -1;
    }
}


void open_ship_editor(GuiContext *gui) {
    GtkWidget *editor_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(editor_window), "Editor lodičiek");
    gtk_window_set_default_size(GTK_WINDOW(editor_window), 800, 800);

    g_signal_connect(editor_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(editor_window, "delete-event", G_CALLBACK(on_editor_window_close), gui);

    // Hlavný grid
    GtkWidget *main_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(editor_window), main_grid);

    // Editor hracej plochy naľavo

    create_grid(gui, true, G_CALLBACK(handle_ship_placement),false,true);
    gtk_grid_attach(GTK_GRID(main_grid), gui->hracovaPlochaGrid, 0, 0, 1, 1);

    // Panel s lodičkami napravo
    GtkWidget *ships_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(ships_box, "ships-box"); // CSS pre ohraničenie
    gtk_grid_attach(GTK_GRID(main_grid), ships_box, 1, 0, 1, 1);

    // Popis pre pravý panel
    GtkWidget *description_label = gtk_label_new("Dostupné lodičky:");
    gtk_widget_set_name(description_label, "coordinate-label");
    gtk_box_pack_start(GTK_BOX(ships_box), description_label, FALSE, FALSE, 0);

    const char *ship_images[] = {
        "../Grafika/Lodicka5_H.png",
        "../Grafika/Lodicka4_H.png",
        "../Grafika/Lodicka3_H.png",
        "../Grafika/Lodicka2_H.png"
    };

    for (int i = 1; i <= 4; i++) {
        GtkWidget *ship_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(ships_box), ship_row, FALSE, FALSE, 0);

        GtkWidget *ship_image = gtk_image_new_from_file(ship_images[i-1]);
        gtk_box_pack_start(GTK_BOX(ship_row), ship_image, FALSE, FALSE, 0);

        char count_text[20];

        snprintf(count_text, sizeof(count_text), "x %d", i);
        GtkWidget *ship_count_label = gtk_label_new(count_text);
        gtk_widget_set_name(ship_count_label, "coordinate-label");

        gtk_box_pack_start(GTK_BOX(ship_row), ship_count_label, FALSE, FALSE, 0);
    }

    // Potvrdzovacie tlačidlo
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(button_box), TRUE);
    gtk_grid_attach(GTK_GRID(main_grid), button_box, 0, 1, 2, 1);

    gui->confirm_button = gtk_button_new_with_label("Confirm");
    gtk_box_pack_start(GTK_BOX(button_box), gui->confirm_button, FALSE, FALSE, 0);

    g_signal_connect(gui->confirm_button, "clicked", G_CALLBACK(on_confirm_clicked), gui);

    gtk_widget_show_all(editor_window);

    // Spustenie blokujúcej slučky pre editor
    gtk_main();
}

void on_start_game_clicked(GtkWidget *widget, gpointer data) {
    // Simulácia úspešného pripojenia na server
    int result = 1; // 1 = úspech, 0 = druhý hráč nie je pripojený, -1 = chyba
    GuiContext *gui = (GuiContext*)data;

    if (result == 1) {
        g_print("Druhý hráč je pripojený. Spúšťame hru...\n");

        // Zavretie aktuálneho okna (okno s tlačidlom)
        GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
        if (gtk_widget_is_toplevel(toplevel)) {
            gtk_widget_destroy(toplevel); // Zničí hlavné okno
        }

        // Otvorenie editoru lodí
        open_ship_editor(gui);
    } else if (result == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(
            NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Druhý hráč nie je pripojený. Skúste neskôr."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(
            NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Chyba pri pripojení na server."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


void create_main_window(GuiContext* gui) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Battleships - Úvodné okno");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Hlavný box
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Popis
    GtkWidget *label = gtk_label_new("Vitajte v hre Battleships! Kliknite na tlačidlo pre začiatok hry.");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    // Tlačidlo na začatie hry
    GtkWidget *start_button = gtk_button_new_with_label("Začať hru");
    gtk_box_pack_start(GTK_BOX(box), start_button, TRUE, TRUE, 0);

    // Callback funkcia pre tlačidlo
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_game_clicked), gui);

    gtk_widget_show_all(window);
    // Spustenie blokujúcej slučky pre editor
    gtk_main();
}