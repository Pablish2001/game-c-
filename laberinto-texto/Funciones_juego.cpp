#include "funciones_juego.h"
#include "allegroManager.h"
#include <fstream>

char menu_inicio(AllegroManager& allegro) {

    ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
    if (!allegro.getFont()) return '3';

    struct Boton {
        float x, y, w, h;
        std::string texto;
        char opcion;
    };

    Boton botones[] = {
        {350, 150, 300, 60, "Laberinto grande", '1'},
        {350, 250, 300, 60, "Laberinto pequenio", '2'},
        {350, 350, 300, 60, "Salir", '3'}
    };
    int width = al_get_display_width(allegro.getDisplay());
    int height = al_get_display_height(allegro.getDisplay());

    ALLEGRO_EVENT evento;

    allegro.mostrarPantalla();
    while (true) {

        int cuadroX1 = 150, cuadroY1 = 80;
        int cuadroX2 = width - 150, cuadroY2 = height - 150;
        al_draw_filled_rounded_rectangle(cuadroX1, cuadroY1, cuadroX2, cuadroY2, 0, 0, al_map_rgba(30, 30, 30,220));
        al_draw_rectangle(cuadroX1, cuadroY1, cuadroX2, cuadroY2, blanco, 2.0);

        for (const Boton& b : botones) {
            al_draw_filled_rounded_rectangle(b.x, b.y, b.x + b.w, b.y + b.h,20,20, al_map_rgb(50, 80, 200));
            al_draw_text(allegro.getFont(), al_map_rgb(255, 255, 255), b.x + 80, b.y + 20, 0, b.texto.c_str());
        }

        al_flip_display();
        al_wait_for_event(allegro.getEventQueue(), &evento);

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            float mx = evento.mouse.x;
            float my = evento.mouse.y;
            for (const Boton& b : botones) {
                if (mx >= b.x && mx <= b.x + b.w && my >= b.y && my <= b.y + b.h) {
                    return b.opcion;
                }
            }
        }
    }
}

void cargar_laberinto_desde_archivo(const std::string& ruta, char laberinto[50][50], int& filas, int& columnas) {
    std::ifstream archivo(ruta);
    std::string linea;
    filas = 0;
    columnas = 0;
    while (std::getline(archivo, linea) && filas < 50) {
        for (size_t i = 0; i < linea.length() && i < 50; ++i) {
            laberinto[filas][i] = linea[i];
        }
        columnas = std::max(columnas, (int)linea.length());
        ++filas;
    }
}

void iniciar_laberinto(char opc,AllegroManager* allegro) {
    char laberinto[50][50];
    int filas = 0, columnas = 0;

    if (opc == '1') {
        cargar_laberinto_desde_archivo("text/laberinto_grande.txt", laberinto, filas, columnas);
    } else if (opc == '2') {
        cargar_laberinto_desde_archivo("text/laberinto_pequeno.txt", laberinto, filas, columnas);
    } else {
        return;
    }

    Laberinto lab(filas, columnas, laberinto);
    ciclo_juego(lab, allegro);
}
void pregunta_gnomo(AllegroManager* allegro, Laberinto *laberinto, int pos_fila, int pos_col) {
    Gnomos *gnomo = laberinto->obtener_Gnomo(pos_fila, pos_col);
    if (gnomo->hacerPregunta(allegro->getDisplay(),allegro->getEventQueue(),allegro->getImagenes())) {
        Tesoro *tesoro = new Tesoro(gnomo->get_valor_de_tesoro());
        laberinto->asignarTesoro(pos_fila, pos_col, tesoro);
        laberinto->get_Jugador()->incrementar_gnomos_acertados();
    } else {
        laberinto->limpiar_casilla(pos_fila, pos_col);
    }
}

bool sobrevivir_dragon(AllegroManager* allegro,Laberinto *laberinto, int pos_fila, int pos_col) {
    Dragon *dragon = laberinto->obtener_dragon(pos_fila, pos_col);
    if (dragon->verificarTesoros(allegro,laberinto->get_Jugador())) {
        laberinto->limpiar_casilla(pos_fila, pos_col);
        laberinto->get_Jugador()->incrementar_dragones_derrotados();
        return true;
    } else {
        return false;
    }
}

int verificar_adyacencias(Laberinto *laberinto,AllegroManager* allegro) {
    std::pair<int, int> posicionGnomo = laberinto->jugadorAdyacente('G');
    if (posicionGnomo.first != -1 && posicionGnomo.second != -1) {
        pregunta_gnomo(allegro,laberinto, posicionGnomo.first, posicionGnomo.second);
        return 0;
    }

    std::pair<int, int> posicionDragon = laberinto->jugadorAdyacente('D');
    if (posicionDragon.first != -1 && posicionDragon.second != -1) {
        if (sobrevivir_dragon(allegro,laberinto, posicionDragon.first, posicionDragon.second)) {
            return 0;
        } else {
            return -1;
        }
    }
    return 1;
}

bool procesar_movimiento(Laberinto *laberinto, char movimiento) {
    if (movimiento == 'w' || movimiento == 's' || movimiento == 'a' || movimiento == 'd') {
        int nuevaFila = laberinto->getPosJugadorFila();
        int nuevaColumna = laberinto->getPosJugadorColumna();

        switch (movimiento) {
            case 'w': nuevaFila--; break;
            case 's': nuevaFila++; break;
            case 'a': nuevaColumna--; break;
            case 'd': nuevaColumna++; break;
        }

        if (laberinto->moverJugador(nuevaFila, nuevaColumna) != -1) {
            return true;
        } else {
            return false;
        }
    } else {
        std::cout << "\nMovimiento invalido. Usa 'w', 's', 'a' o 'd'.\n";
        system("pause");
        return true;
    }
}

bool teclaPresionada[ALLEGRO_KEY_MAX] = {false};

void mover(Laberinto *laberinto, ALLEGRO_EVENT_QUEUE *event_queue, bool &seguir_juego) {
    ALLEGRO_EVENT ev;

    while (true) {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            seguir_juego = false;
            return;
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            int nuevaFila = laberinto->getPosJugadorFila();
            int nuevaColumna = laberinto->getPosJugadorColumna();

            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_W: nuevaFila--; break;
                case ALLEGRO_KEY_S: nuevaFila++; break;
                case ALLEGRO_KEY_A: nuevaColumna--; break;
                case ALLEGRO_KEY_D: nuevaColumna++; break;
                default: return;
            }

            if (laberinto->moverJugador(nuevaFila, nuevaColumna) != -1) {
                seguir_juego = true;
            } else {
                seguir_juego = false;
            }
            return;
        }
    }
}


void ciclo_juego(Laberinto &lab, AllegroManager* allegro) {
    bool seguir_juego = true;
    int monstruos_cerca = 1;

    do {
        allegro->mostrarPantalla();
        lab.imprimirLaberinto(allegro);

        monstruos_cerca = verificar_adyacencias(&lab,allegro);
        if (monstruos_cerca == 0) {
            continue;
        } else if (monstruos_cerca == -1) {
            seguir_juego = false;
        } else {
            mover(&lab, allegro->getEventQueue(), seguir_juego);
            al_flush_event_queue(allegro->getEventQueue());
        }
    } while (seguir_juego);
}

