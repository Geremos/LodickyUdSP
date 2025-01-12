//
// Created by juraj on 12. 1. 2025.
//

#include "HraciaPlocha.h"


#include <stdio.h>
#include <stdlib.h>
extern GtkWidget *buttons[VELKOST_PLOCHY][VELKOST_PLOCHY];

// Tlačidlá pre hraciu plochu
void init_hraciaPlocha(HraciaPlocha* hraciaPlocha)
{
    hraciaPlocha->hraciaPlocha = (Policko**)malloc(VELKOST_PLOCHY * sizeof(Policko*));
    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        hraciaPlocha->hraciaPlocha[i] = (Policko*)malloc(VELKOST_PLOCHY * sizeof(Policko));
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            init_Policko(&hraciaPlocha->hraciaPlocha[i][j], i, j);
        }
    }
}

Policko* getPolicko(int x, int y, HraciaPlocha* hraciaPlocha)
{
    return &hraciaPlocha->hraciaPlocha[x][y];
}

void vypis(HraciaPlocha* hraciaPlocha) {
    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            // Priamo vypíše znak reprezentovaný enumom TypPolickaEnum
            printf("%c ", hraciaPlocha->hraciaPlocha[i][j].typPolicka);
        }
        printf("\n");
    }
}


bool nastavLodicku(enum LodickaEnum typLodicky, int zX, int zY, int kX, int kY, HraciaPlocha* hraciaPlocha)
{
    if (zX < 0 || zY < 0 || kX < 0 || kY < 0 || zX >= VELKOST_PLOCHY || zY >= VELKOST_PLOCHY || kX >= VELKOST_PLOCHY || kY >= VELKOST_PLOCHY)
    {
        return false;
    }
    if (zX > kX || zY > kY)
    {
        return false;
    }
    if (kX - zX != typLodicky - 1 && kY - zY != typLodicky - 1)
    {
        return false;
    }
    for (int i = zX; i <= kX; i++)
    {
        for (int j = zY; j <= kY; j++)
        {
            if (hraciaPlocha->hraciaPlocha[i][j].lodickaEnum != noShip)
            {
                return false;
            }
        }
    }
    for (int i = zX; i <= kX; i++)
    {
        for (int j = zY; j <= kY; j++)
        {
            hraciaPlocha->hraciaPlocha[i][j].lodickaEnum = typLodicky;
        }
    }
    return true;
}

bool on_button_clicked(GtkWidget *widget, gpointer data) {
        Policko *policko = (Policko *)data;

        g_print("Kliknuté na políčko: (%d, %d)\n", policko->x, policko->y);

        // Kontrola, či už bolo na políčko vystrelené
        if (policko->strela) {
            g_print("Na toto políčko už bolo vystrelené.\n");
            return false;
        }

        // Výber obrázka na prekrytie
        const char *image_path;
        if (policko->lodickaEnum != noShip) {
            image_path = "../GUI_res/lodicka.png"; // Zasiahnutá loď
        } else {
            image_path = "../GUI_res/strela.png"; // Výbuch na vode
        }

        // Vytvorenie nového obrázka
        GtkWidget *new_image = gtk_image_new_from_file(image_path);

        // Nahradenie existujúceho obrázka tlačidla novým obrázkom
        gtk_button_set_image(GTK_BUTTON(widget), new_image);

        // Nastavenie stavu políčka ako zasiahnutého
        setStrela(policko);
        return true;
}


void create_grid(GtkWidget *grid, HraciaPlocha *hraciaPlocha) {
    for (int i = 0; i < VELKOST_PLOCHY; i++) {
        for (int j = 0; j < VELKOST_PLOCHY; j++) {
            buttons[i][j] = gtk_button_new();
            gtk_widget_set_size_request(buttons[i][j], 60, 60);
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j, i, 1, 1);

            // Set initial image for water
            GtkWidget *water_image = gtk_image_new_from_file("../GUI_res/voda.png");
            gtk_button_set_image(GTK_BUTTON(buttons[i][j]), water_image);

            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(on_button_clicked), &hraciaPlocha->hraciaPlocha[i][j]);
        }
    }
}

void destroy_hraciaPlocha(HraciaPlocha* hraciaPlocha)
{
    for (int i = 0; i < VELKOST_PLOCHY; i++)
    {
        free(hraciaPlocha->hraciaPlocha[i]);
        hraciaPlocha->hraciaPlocha[i] = NULL;
    }
    free(hraciaPlocha->hraciaPlocha);
    hraciaPlocha->hraciaPlocha = NULL;
}






