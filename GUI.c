//
// Created by juraj on 13. 1. 2025.
//
#include "gui.h"

static GtkWidget *oponentovaPlochaGrid;
static GtkWidget *hracovaPlochaGrid;
static GtkWidget *infoBox; // Stredný panel so skóre a informáciami
static GtkWidget *editor_grid;
static GtkWidget *confirm_button;

void strela(GtkWidget *widget, gpointer data) {
    // Získanie ukazovateľa na konkrétne políčko
    Policko *policko = (Policko *)data;

    g_print("Kliknuté na políčko: (%d, %d)\n", policko->x, policko->y);

    // Kontrola, či už bolo na políčko vystrelené
    if (policko->strela) {
        g_print("Na toto políčko už bolo vystrelené.\n");
        return;
    }

    // Výber obrázka na základe stavu políčka
    const char *image_path;
    if (policko->lodickaEnum != noShip) {
        image_path = "../GUI_res/lodicka.png"; // Zasiahnutá loď
    } else {
        image_path = "../GUI_res/strela.png"; // Výbuch na vode
    }

    // Aktualizácia obrázka tlačidla
    GtkWidget *image = gtk_image_new_from_file(image_path);
    gtk_button_set_image(GTK_BUTTON(widget), image);

    // Nastavenie stavu políčka ako zasiahnutého
    setStrela(policko);
}


void create_grid(GtkWidget *grid, HraciaPlocha *plocha, bool is_interactive, bool editor) {
    // Pridanie súradníc ako hlavičky
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            if (i == 0 && j == 0) {
                // Prázdny roh
                GtkWidget *empty_label = gtk_label_new("");
                gtk_grid_attach(GTK_GRID(grid), empty_label, j, i, 1, 1);
            } else if (i == 0) {
                // Čísla hore (1, 2, 3, ...)
                GtkWidget *label = gtk_label_new(g_strdup_printf("%d", j));
                // Pridanie CSS triedy
                gtk_widget_set_name(label, "coordinate-label");

                gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1);
            } else if (j == 0) {
                // Písmená na boku (A, B, C, ...)
                GtkWidget *label = gtk_label_new(g_strdup_printf("%c", 'A' + i - 1));
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
                if (is_interactive)
                {
                    if (editor) {
                        g_signal_connect(button, "clicked", G_CALLBACK(suradnica_lodicky), plocha->hraciaPlocha[i - 1] + j - 1);
                    } else {
                        g_signal_connect(button, "clicked", G_CALLBACK(strela), plocha->hraciaPlocha[i - 1] + j - 1);
                    }
                }
                gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);

                // Uvoľnenie zdrojov
                g_object_unref(sub_pixbuf);
                g_object_unref(original_pixbuf);
            }
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
    create_grid(oponentovaPlochaGrid, oponent, true,false);
    gtk_grid_attach(GTK_GRID(mainGrid), oponentovaPlochaGrid, 0, 0, 1, 1);

    // Stredný panel (info o skóre, správy, stav hry)
    infoBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new("Zobrazovanie skóre a stavu hry");
    gtk_box_pack_start(GTK_BOX(infoBox), label, FALSE, FALSE, 0);
    gtk_grid_attach(GTK_GRID(mainGrid), infoBox, 1, 0, 1, 1);

    // Hracova hracia plocha (vpravo)
    hracovaPlochaGrid = gtk_grid_new();
    create_grid(hracovaPlochaGrid, hrac,true,false);
    gtk_grid_attach(GTK_GRID(mainGrid), hracovaPlochaGrid, 2, 0, 1, 1);

    gtk_widget_show_all(window);
}


void suradnica_lodicky(GtkWidget *widget, gpointer data) {
    Policko *policko = (Policko *)data;
    // Tlačidlo pre mriežku
    GtkWidget *button = gtk_button_new();
    gtk_widget_set_size_request(button, 60, 60);
    // Uvoľnenie zdrojov

    // Prepnúť stav políčka medzi "loď" a "voda"
    if (policko->lodickaEnum == noShip) {
        policko->lodickaEnum = lodicka; // Alebo iný typ lode
        GtkWidget *image = gtk_image_new_from_file("../GUI_res/lodicka.png");
        gtk_button_set_image(GTK_BUTTON(widget), image);
    } else {
        policko->lodickaEnum = noShip;
        // Nastavenie obrázku podľa obsahu políčka
        GdkPixbuf *original_pixbuf = gdk_pixbuf_new_from_file("../Grafika/Background.png", NULL);
        GdkPixbuf *sub_pixbuf = gdk_pixbuf_new_subpixbuf(
            original_pixbuf,
            (policko->y - 1) * 60, (policko->x - 1) * 60, // Orezanie časti obrázka
            60, 60
        );
        GtkWidget *image = gtk_image_new_from_pixbuf(sub_pixbuf);
        gtk_button_set_image(GTK_BUTTON(button), image);
        g_object_unref(sub_pixbuf);
        g_object_unref(original_pixbuf);
    }
}


void on_confirm_clicked(GtkWidget *widget, gpointer data) {
    static bool editor_closed = false;

    if (editor_closed) {
        // Ak už bolo tlačidlo stlačené, nerob nič
        return;
    }

    editor_closed = true;

    // Zavretie editorového okna
    GtkWidget *editor_window = GTK_WIDGET(data);
    gtk_widget_destroy(editor_window); // Zničí okno editoru

    g_print("Lodičky hráča boli potvrdené a editor zatvorený.\n");
}

void open_ship_editor(HraciaPlocha *player_board) {
    GtkWidget *editor_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(editor_window), "Editor lodičiek");
    gtk_window_set_default_size(GTK_WINDOW(editor_window), 800, 800);

    g_signal_connect(editor_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *editor_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(editor_window), editor_layout);

    editor_grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(editor_layout), editor_grid, TRUE, TRUE, 0);

    create_grid(editor_grid, player_board,true,true);

    confirm_button = gtk_button_new_with_label("Potvrdiť a začať hru");
    gtk_box_pack_start(GTK_BOX(editor_layout), confirm_button, FALSE, FALSE, 0);

    g_signal_connect(confirm_button, "clicked", G_CALLBACK(on_confirm_clicked), editor_window);

    gtk_widget_show_all(editor_window);

    gtk_main();
}