#include "arreglobombas.h"

ArregloBombas::ArregloBombas() : totalBombas(1) {}

ArregloBombas::~ArregloBombas() {
    for (Bomba* bomba : ArrBombas) {
        delete bomba;
    }
}

void ArregloBombas::crearUnaBomba(int x, int y) {
    /*
    if (ArrBombas.size() < totalBombas) {
         Bomba* bomba = new Bomba(jugadorX, jugadorY, mapajuego, nullptr);

        // Conectamos la señal de explosión completa de la bomba al slot `bombaExplotada`
        connect(nuevaBomba, &Bomba::explosionCompleta, this, &ArregloBombas::bombaExplotada);

        ArrBombas.push_back(nuevaBomba);
    }
}

void ArregloBombas::bombaExplotada() {
    // Cuando una bomba explota, la eliminamos del vector y liberamos su memoria
    if (!ArrBombas.empty()) {
        delete ArrBombas.back();
        ArrBombas.pop_back();
    }
}
*/
}
