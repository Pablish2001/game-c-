#ifndef LABERINTO_H
#define LABERINTO_H

#include "dragon.h"
#include "gnomo.h"
#include "jugador.h"
#include "tesoro.h"
#include "allegroManager.h"


class Laberinto {
private:
    char matrizLaberinto[50][50] = {};
    void* objetosLaberinto[50][50] = {};
    int filas;
    int columnas;
    int posJugadorFila;
    int posJugadorColumna;

public:
    Laberinto(int filas, int columnas, char laberinto[][50]);

    Gnomos* obtener_Gnomo(int fila, int columna);
    Dragon* obtener_dragon(int fila, int columna);
    void asignarTesoro(int fila, int columna, Tesoro* tesoro);
    void asignarJugador(int fila, int columna, Jugador* jugador);
    void asignarGnomo(int fila, int columna, Gnomos* gnomos);
    void asignarDragon(int fila, int columna, Dragon* dragon);
    void limpiar_casilla(int fila, int columna);

    void imprimirLaberinto(AllegroManager* allegro);
    void stats_jugador(AllegroManager* allegro);

    int getPosJugadorFila();
    int getPosJugadorColumna();
    Jugador* get_Jugador();

    int moverJugador(int nuevaFila, int nuevaColumna);

    std::pair<int, int> jugadorAdyacente(char objetivo);

};

#endif

