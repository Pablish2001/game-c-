#include "laberinto.h"
#include <ctime>

Laberinto::Laberinto(int filas, int columnas, char laberinto[][50]) {
    this->filas = filas;
    this->columnas = columnas;

    int tesoros_totales = 0;
    srand(time(0));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (laberinto[i][j] == 'I') {
                this->posJugadorFila = i;
                this->posJugadorColumna = j;

                matrizLaberinto[i][j] = 'I';
                Jugador* jugador = new Jugador();
                this->asignarJugador(i, j, jugador);
            } else if (laberinto[i][j] == 'G') {
                int valor_aleatorio = rand() % 5 + 1;
                Gnomos* gnomos = new Gnomos(valor_aleatorio);
                this->asignarGnomo(i, j, gnomos);
                tesoros_totales += valor_aleatorio;
            } else if (laberinto[i][j] == 'D') {
                int valor_aleatorio = rand() % tesoros_totales + 1;
                if (valor_aleatorio > (tesoros_totales * 0.5)) {
                    valor_aleatorio -= (tesoros_totales * 0.3);
                }
                Dragon* dragon = new Dragon(valor_aleatorio);
                this->asignarDragon(i, j, dragon);
                tesoros_totales -= valor_aleatorio;
            } else {
                matrizLaberinto[i][j] = laberinto[i][j];
                objetosLaberinto[i][j] = nullptr;
            }
        }
    }
}

Gnomos* Laberinto::obtener_Gnomo(int fila, int columna) {
    if (matrizLaberinto[fila][columna] == 'G') {
        return static_cast<Gnomos*>(objetosLaberinto[fila][columna]);
    }
    return nullptr;
}

Dragon* Laberinto::obtener_dragon(int fila, int columna) {
    if (matrizLaberinto[fila][columna] == 'D') {
        return static_cast<Dragon*>(objetosLaberinto[fila][columna]);
    }
    return nullptr;
}

void Laberinto::asignarTesoro(int fila, int columna, Tesoro* tesoro) {
    objetosLaberinto[fila][columna] = tesoro;
    matrizLaberinto[fila][columna] = 'T';
}

void Laberinto::asignarJugador(int fila, int columna, Jugador* jugador) {
    objetosLaberinto[fila][columna] = jugador;
}

void Laberinto::asignarGnomo(int fila, int columna, Gnomos* gnomos) {
    objetosLaberinto[fila][columna] = gnomos;
    matrizLaberinto[fila][columna] = 'G';
}

void Laberinto::asignarDragon(int fila, int columna, Dragon* dragon) {
    objetosLaberinto[fila][columna] = dragon;
    matrizLaberinto[fila][columna] = 'D';
}

void Laberinto::limpiar_casilla(int fila, int columna) {
    objetosLaberinto[fila][columna] = nullptr;
    matrizLaberinto[fila][columna] = ' ';
}

void Laberinto::imprimirLaberinto(AllegroManager* allegro) {
    ALLEGRO_BITMAP** arregloImagenes = allegro->getImagenes();
    int celda_ancho = al_get_display_width(allegro->getDisplay()) / (this->columnas / 0.7);
    int celda_alto = al_get_display_height(allegro->getDisplay()) / this->filas;

    for (int i = 0; i < this->filas; ++i) {
        for (int j = 0; j < this->columnas; ++j) {
            switch (matrizLaberinto[i][j]) {
                case 'P': al_draw_bitmap(arregloImagenes[0], j * celda_ancho, i * celda_alto, 0); break;
                case 'J': al_draw_bitmap(arregloImagenes[1], j * celda_ancho, i * celda_alto, 0); break;
                case 'I': al_draw_bitmap(arregloImagenes[2], j * celda_ancho, i * celda_alto, 0); break;
                case 'G': al_draw_bitmap(arregloImagenes[3], j * celda_ancho, i * celda_alto, 0); break;
                case 'D': al_draw_bitmap(arregloImagenes[4], j * celda_ancho, i * celda_alto, 0); break;
                case 'S': al_draw_bitmap(arregloImagenes[5], j * celda_ancho, i * celda_alto, 0); break;
                case 'T': al_draw_bitmap(arregloImagenes[6], j * celda_ancho, i * celda_alto, 0); break;
            }
        }
    }
    this->stats_jugador(allegro);
}

int Laberinto::getPosJugadorFila() {
    return this->posJugadorFila;
}

int Laberinto::getPosJugadorColumna() {
    return this->posJugadorColumna;
}

Jugador* Laberinto::get_Jugador() {
    return static_cast<Jugador*>(objetosLaberinto[posJugadorFila][posJugadorColumna]);
}

int Laberinto::moverJugador(int nuevaFila, int nuevaColumna) {
    if (nuevaFila >= 0 && nuevaFila < filas && nuevaColumna >= 0 && nuevaColumna < columnas) {
        char destino = matrizLaberinto[nuevaFila][nuevaColumna];
        if (destino == 'S') {
            return -1;  // Encontró la salida
        } else if (destino == 'P' || destino == 'X') {
            return 0;   // Pared o inválido
        } else {
            if (destino == 'T') {
                Tesoro* tesoro = static_cast<Tesoro*>(objetosLaberinto[nuevaFila][nuevaColumna]);
                get_Jugador()->incremento_tesoro(tesoro->entregar_tesoro());
            }

            if (destino != 'I') {
                matrizLaberinto[nuevaFila][nuevaColumna] = 'J';
            }

            objetosLaberinto[nuevaFila][nuevaColumna] = objetosLaberinto[posJugadorFila][posJugadorColumna];
            objetosLaberinto[posJugadorFila][posJugadorColumna] = nullptr;

            if (matrizLaberinto[posJugadorFila][posJugadorColumna] != 'I') {
                matrizLaberinto[posJugadorFila][posJugadorColumna] = ' ';
            }

            posJugadorFila = nuevaFila;
            posJugadorColumna = nuevaColumna;

            get_Jugador()->incrementar_pasos();
            return 1;
        }
    }
    return 0;
}

void Laberinto::stats_jugador(AllegroManager* allegro) {
    Jugador* jugador = get_Jugador();
    jugador->imprimirValores(allegro);
}

std::pair<int, int> Laberinto::jugadorAdyacente(char objetivo) {
    int f = posJugadorFila, c = posJugadorColumna;
    int offsets[8][2] = { {-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1} };
    for (auto& offset : offsets) {
        int nf = f + offset[0], nc = c + offset[1];
        if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && matrizLaberinto[nf][nc] == objetivo) {
            return {nf, nc};
        }
    }
    return {-1, -1};
}
