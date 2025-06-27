#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "jugador.h"
#include "dragon.h"



Dragon::Dragon(int tesorosReq) {
    this->tesorosRequeridos = tesorosReq;
}

int Dragon::get_tesoro() {
    return tesorosRequeridos;
}

bool Dragon::verificarTesoros(AllegroManager* allegro, Jugador* jugador) {
    // Obtener recursos desde el objeto allegro
    ALLEGRO_DISPLAY* display = allegro->getDisplay();
    ALLEGRO_FONT* font       = allegro->getFont();
    ALLEGRO_BITMAP** imagenes = allegro->getImagenes();
    ALLEGRO_EVENT_QUEUE* queue = allegro->getEventQueue();

    int width  = al_get_display_width(display);
    int height = al_get_display_height(display);

    ALLEGRO_COLOR rojo     = al_map_rgb(200, 0, 0);
    ALLEGRO_COLOR verde    = al_map_rgb(0, 200, 0);
    ALLEGRO_COLOR blanco   = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR fondoBox = al_map_rgb(20, 20, 20);

    std::string linea1 = "Tesoro requerido para el dragon: (" + std::to_string(tesorosRequeridos) + ").";
    std::string linea2;
    ALLEGRO_COLOR colorTexto;

    bool exito = jugador->get_tesoros() >= tesorosRequeridos;

    if (exito) {
        linea2 = "Estas a salvo! Tienes suficientes tesoros.";
        colorTexto = verde;
        jugador->decremento_tesoro(tesorosRequeridos);
    } else {
        linea2 = "El dragon te devorar! No tienes suficientes tesoros.";
        colorTexto = rojo;
    }

    bool mostrar = true;

    while (true) {
        if (mostrar) {
            allegro->mostrarPantalla();

            // Cuadro modal
            al_draw_filled_rounded_rectangle(100, 150, width - 100, height - 150, 0, 0, fondoBox);
            al_draw_rectangle(100, 150, width - 100, height - 150, blanco, 2);

            // Mensajes
            al_draw_text(font, blanco, width / 2, 180, ALLEGRO_ALIGN_CENTER, linea1.c_str());
            al_draw_text(font, colorTexto, width / 2, 240, ALLEGRO_ALIGN_CENTER, linea2.c_str());


            al_draw_bitmap(imagenes[4], width / 2 - al_get_bitmap_width(imagenes[4])/ 2, 280, 0);

            // Instrucción
            al_draw_text(font, blanco, width / 2, height - 180, ALLEGRO_ALIGN_CENTER, "Haz clic para continuar...");

            al_flip_display();
            mostrar = false;
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            break;

        if (ev.type == ALLEGRO_EVENT_DISPLAY_EXPOSE || ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN)
            mostrar = true;

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            exit(0);  // Finaliza el juego de forma segura
    }

    return exito;
}


