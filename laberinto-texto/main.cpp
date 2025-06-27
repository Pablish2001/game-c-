//includes para allegro
#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "AllegroManager.h"
#include "funciones_juego.h"
using namespace std;


int main() {

 AllegroManager allegro;

    if (!allegro.inicializar()) {
        std::cerr << "Error inicializando Allegro\n";
        return -1;
    }

    allegro.cargarImagenes();

 char opc;

    do{

        opc = menu_inicio(allegro);
        if (opc!='3'){
            iniciar_laberinto(opc,&allegro);
        }

    //allegro.~AllegroManager();
    }while(opc!='3');

    return 0;
}


