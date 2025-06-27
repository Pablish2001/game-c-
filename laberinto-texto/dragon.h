#ifndef DRAGON_H
#define DRAGON_H

#include <iostream>
#include "jugador.h"
#include "allegroManager.h"

class Dragon {

private:
    int tesorosRequeridos;

public:
    int get_tesoro();
    Dragon(int tesorosReq);
    bool verificarTesoros(AllegroManager* allegro, Jugador* jugador);










};


#endif // DRAGON_H

