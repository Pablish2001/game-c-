#ifndef JUGADOR_H
#define JUGADOR_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "allegroManager.h"

class Jugador {
private:
    int pasos;
    int tesoros;
    int gnomos_acertados;
    int dragones_derrotados;

public:
    Jugador();

    int get_tesoros();
    void incrementar_pasos();
    void incremento_tesoro(int cantidad);
    void decremento_tesoro(int cantidad);
    void incrementar_gnomos_acertados();
    void incrementar_dragones_derrotados();

    void imprimirValores(AllegroManager* allegro);
};

#endif
