// funciones_juego.h
#ifndef FUNCIONES_JUEGO_H
#define FUNCIONES_JUEGO_H

#include "dragon.h"
#include "gnomo.h"
#include "jugador.h"
#include "tesoro.h"
#include "laberinto.h"
#include "allegroManager.h"

#include <iostream>
#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>


char menu_inicio(AllegroManager& allegro);
void iniciar_laberinto(char opc, AllegroManager* allegro);
void pregunta_gnomo(AllegroManager* allegro,Laberinto *laberinto, int pos_fila, int pos_col);
bool sobrevivir_dragon(AllegroManager* allegro,Laberinto *laberinto, int pos_fila, int pos_col);
int verificar_adyacencias(Laberinto *laberinto,AllegroManager* allegro);
bool procesar_movimiento(Laberinto *laberinto, char movimiento);
void mover(Laberinto *laberinto, ALLEGRO_EVENT_QUEUE *event_queue, bool &seguir_juego);
void ciclo_juego(Laberinto &lab,AllegroManager* allegro);

#endif

