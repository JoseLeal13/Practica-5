// puerta.cpp
#include "puerta.h"

Puerta::Puerta(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap) {
    puerta->setPos(100, 100);  // Posición en la escena
    sceneActual->addItem(puerta);
}
