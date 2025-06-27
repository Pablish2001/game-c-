#include "jugador.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <cstdio>

Jugador::Jugador() {
    this->pasos = 0;
    this->tesoros = 0;
    this->gnomos_acertados = 0;
    this->dragones_derrotados = 0;
}

int Jugador::get_tesoros() {
    return this->tesoros;
}

void Jugador::incrementar_pasos() {
    this->pasos++;
}

void Jugador::incremento_tesoro(int cantidad) {
    this->tesoros += cantidad;
}

void Jugador::decremento_tesoro(int cantidad) {
    this->tesoros -= cantidad;
}

void Jugador::incrementar_gnomos_acertados() {
    this->gnomos_acertados++;
}

void Jugador::incrementar_dragones_derrotados() {
    this->dragones_derrotados++;
}

void Jugador::imprimirValores(AllegroManager* allegro) {
    ALLEGRO_BITMAP** arregloImagenes = allegro->getImagenes();
    ALLEGRO_FONT* font = allegro->getFont();

    int anchoEstadisticas = al_get_display_width(allegro->getDisplay()) * 0.3;
    int anchoLaberinto = al_get_display_width(allegro->getDisplay()) * 0.7;

    al_draw_multiline_textf(
        font,
        al_map_rgb(0, 0, 0),
        anchoLaberinto + anchoEstadisticas / 2,
        al_get_font_line_height(font) + 20,
        30,
        15,
        ALLEGRO_ALIGN_CENTER,
        "ESTADISTICAS\nPASOS-DADOS:%d\nCANTIDAD-TESORO:%d\nGNOMOS-ACERTADOS:%d\nDRAGONES-DERROTADOS:%d",
        pasos, tesoros, gnomos_acertados, dragones_derrotados
    );

    al_draw_bitmap(arregloImagenes[8], 725, 380, 0);
    al_flip_display();
}

