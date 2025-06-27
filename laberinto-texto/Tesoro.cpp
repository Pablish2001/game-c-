#include "Tesoro.h"

Tesoro::Tesoro(int valor_entrada) {
    this->valor = valor_entrada;
}

int Tesoro::entregar_tesoro() {
    return this->valor;
}

