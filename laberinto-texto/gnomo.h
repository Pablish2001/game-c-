#ifndef GNOMO_H
#define GNOMO_H


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>"

#define MAX_PREGUNTAS 30
#define LONGITUD_PREGUNTA 100
#define LONGITUD_RESPUESTA 50

class Gnomos {
private:
    int valor_de_tesoro;
    char preguntas[MAX_PREGUNTAS][LONGITUD_PREGUNTA];
    char respuestas[MAX_PREGUNTAS][LONGITUD_RESPUESTA];
    char respuestasIncorrectas[MAX_PREGUNTAS][2][LONGITUD_RESPUESTA];
    int totalPreguntas = 0;

    void a_minusculas(std::string& cadena);
    void cargarPreguntas();

public:
    Gnomos(int valor);

    int get_valor_de_tesoro();

    bool hacerPregunta(ALLEGRO_DISPLAY* display,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_BITMAP** imagenes);
};

#endif
