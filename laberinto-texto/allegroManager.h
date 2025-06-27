#ifndef ALLEGRO_MANAGER_H
#define ALLEGRO_MANAGER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

class AllegroManager {
private:
    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;
    ALLEGRO_BITMAP* imagenes[10] = {nullptr};
    ALLEGRO_FONT* font = nullptr;

public:
    AllegroManager();
    ~AllegroManager();

    bool inicializar();
    void cargarImagenes();
    void limpiarPantalla();
    void mostrarPantalla();

    ALLEGRO_DISPLAY* getDisplay();
    ALLEGRO_EVENT_QUEUE* getEventQueue();
    ALLEGRO_BITMAP** getImagenes();
    ALLEGRO_FONT* getFont();
};

#endif
