#include "arreglobombas.h"
#include "bomba.h"
#include "mapa.h"  // Incluye "mapa.h" si es necesario

ArregloBombas::ArregloBombas() : bombaActiva(nullptr) {}

ArregloBombas::~ArregloBombas() {
    // Eliminar la bomba activa si existe
    if (bombaActiva) {
        delete bombaActiva;
    }
}

void ArregloBombas::crearUnaBomba(int x, int y) {
    // Verificar si ya hay una bomba activa
    if (bombaActiva == nullptr) {  // Solo crea la bomba si no hay ninguna activa
        bombaActiva = new Bomba(x, y, nuevoMapa);  // Crear la bomba en la posición (x, y)

        // Conectar la señal de explosión completa de la bomba al slot bombaExplotada
        connect(bombaActiva, &Bomba::explosionCompleta, this, &ArregloBombas::bombaExplotada);
    }
}

void ArregloBombas::bombaExplotada() {
    // Cuando la bomba explota, la eliminamos y permitimos crear otra
    if (bombaActiva) {
        delete bombaActiva;     // Eliminar la bomba activa de la memoria
        bombaActiva = nullptr;  // Restablecer a nullptr para poder colocar una nueva bomba
    }
}
