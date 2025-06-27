#include "gnomo.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <set>
#include "laberinto.h"
#include "allegroManager.h"

Gnomos::Gnomos(int valor) {
    this->valor_de_tesoro = valor;
    cargarPreguntas();
}

void Gnomos::a_minusculas(std::string &cadena) {
    for (char &c : cadena) {
        c = tolower(c);
    }
}

void Gnomos::cargarPreguntas() {
    std::ifstream archivo("text/preguntas_gnomos.txt");
    std::string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            a_minusculas(linea);
            strncpy(preguntas[totalPreguntas], linea.c_str(), LONGITUD_PREGUNTA);

            getline(archivo, linea);
            a_minusculas(linea);
            strncpy(respuestas[totalPreguntas], linea.c_str(), LONGITUD_RESPUESTA);

            getline(archivo, linea);
            a_minusculas(linea);
            strncpy(respuestasIncorrectas[totalPreguntas][0], linea.c_str(), LONGITUD_RESPUESTA);

            getline(archivo, linea);
            a_minusculas(linea);
            strncpy(respuestasIncorrectas[totalPreguntas][1], linea.c_str(), LONGITUD_RESPUESTA);

            totalPreguntas++;
            if (totalPreguntas >= MAX_PREGUNTAS) break;
        }
        archivo.close();
    }
}

int Gnomos::get_valor_de_tesoro() {
    return this->valor_de_tesoro;
}

bool Gnomos::hacerPregunta(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_BITMAP** imagenes) {
    if (totalPreguntas == 0) return false;

    srand(time(nullptr));
    int preguntaAleatoria = rand() % totalPreguntas;
    std::string pregunta = preguntas[preguntaAleatoria];
    std::string respuestaCorrecta = respuestas[preguntaAleatoria];

    // Generar respuestas mezcladas con 1 correcta y 2 falsas del mismo índice
std::vector<std::pair<std::string, bool>> opciones = {
    {respuestas[preguntaAleatoria], true},
    {respuestasIncorrectas[preguntaAleatoria][0], false},
    {respuestasIncorrectas[preguntaAleatoria][1], false}
};
static std::mt19937 rng(std::random_device{}());
std::shuffle(opciones.begin(), opciones.end(), rng);

    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR verde = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR rojo  = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR azulOscuro = al_map_rgba(50, 50, 150, 200);

    int width = al_get_display_width(display);
    int height = al_get_display_height(display);

    while (true) {
        int cuadroX1 = 100, cuadroY1 = 80;
        int cuadroX2 = width - 100, cuadroY2 = height - 80;
        al_draw_filled_rounded_rectangle(cuadroX1, cuadroY1, cuadroX2, cuadroY2, 0, 0, al_map_rgba(30, 30, 30, 220));
        al_draw_rectangle(cuadroX1, cuadroY1, cuadroX2, cuadroY2, blanco, 2.0);

        al_draw_text(font, blanco, width / 2, cuadroY1 + 20, ALLEGRO_ALIGN_CENTER, pregunta.c_str());

        for (int i = 0; i < 3; ++i) {
            int y1 = 150 + i * 100;
            int y2 = y1 + 60;
            al_draw_filled_rounded_rectangle(150, y1, width - 150, y2, 10, 10, azulOscuro);
           al_draw_text(font, blanco, width / 2, y1 + 15, ALLEGRO_ALIGN_CENTER, opciones[i].first.c_str());

        }

        al_draw_bitmap(imagenes[3], 470, 460, 0);

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int x = ev.mouse.x;
            int y = ev.mouse.y;

            for (int i = 0; i < 3; ++i) {
                int y1 = 150 + i * 100;
                int y2 = y1 + 60;
                if (x >= 150 && x <= width - 150 && y >= y1 && y <= y2) {
                    bool correcto = opciones[i].first == respuestaCorrecta;

                    al_draw_filled_rounded_rectangle(width / 2 - 200, height / 2 - 40, width / 2 + 200, height / 2 + 40, 0, 0, al_map_rgb(0, 0, 0));
                    al_draw_rectangle(width / 2 - 200, height / 2 - 40, width / 2 + 200, height / 2 + 40, blanco, 2.0);

                    al_draw_text(
                        font,
                        correcto ? verde : rojo,
                        width / 2,
                        height / 2 - 10,
                        ALLEGRO_ALIGN_CENTER,
                        correcto ? "Correcto!" : "Incorrecto..."
                    );

                    al_flip_display();
                    al_rest(1.5);

                    al_destroy_font(font);
                    return correcto;
                }
            }
        }
    }

    al_destroy_font(font);
    return false;
}
