#include "AllegroManager.h"

AllegroManager::AllegroManager() {}

AllegroManager::~AllegroManager() {
    for (int i = 0; i < 10; ++i)
        if (imagenes[i]) al_destroy_bitmap(imagenes[i]);

    if (font) al_destroy_font(font);
    if (eventQueue) al_destroy_event_queue(eventQueue);
    if (display) al_destroy_display(display);
}

bool AllegroManager::inicializar() {
    if (!al_init()) return false;
    if (!al_install_keyboard()) return false;
    if (!al_install_mouse()) return false;
    if (!al_init_image_addon()) return false;
    if (!al_init_font_addon()) return false;
    if (!al_init_ttf_addon()) return false;
    if (!al_init_primitives_addon()) return false;

    display = al_create_display(980, 620);
    if (!display) return false;
    al_set_window_title(display, "LABERINTO");

    eventQueue = al_create_event_queue();
    if (!eventQueue) return false;

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    font = al_create_builtin_font();
    if (!font) return false;

    return true;
}

void AllegroManager::cargarImagenes() {
    imagenes[0] = al_load_bitmap("img/roca.png");
    imagenes[1] = al_load_bitmap("img/user.png");
    imagenes[2] = al_load_bitmap("img/entrada.png");
    imagenes[3] = al_load_bitmap("img/gnomo.png");
    imagenes[4] = al_load_bitmap("img/dragon.png");
    imagenes[5] = al_load_bitmap("img/salida.png");
    imagenes[6] = al_load_bitmap("img/cofre.png");
    imagenes[7] = al_load_bitmap("img/fondo.png");
    imagenes[8] = al_load_bitmap("img/score.png");
}

void AllegroManager::limpiarPantalla() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void AllegroManager::mostrarPantalla() {
    al_draw_bitmap(imagenes[7], 0, 0, 0);
    al_flip_display();
}

ALLEGRO_DISPLAY* AllegroManager::getDisplay() {
    return display;
}

ALLEGRO_EVENT_QUEUE* AllegroManager::getEventQueue() {
    return eventQueue;
}

ALLEGRO_BITMAP** AllegroManager::getImagenes() {
    return imagenes;
}

ALLEGRO_FONT* AllegroManager::getFont() {
    return font;
}
