#include "jugador.h"
#include <QKeyEvent>

Jugador::Jugador(int startX, int startY, QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent), x(startX), y(startY), speed_x(0), speed_y(0)
{
    setPos(x, y); // Establece la posición inicial
    setFlag(QGraphicsItem::ItemIsFocusable); // Hacer que el objeto sea "focusable"
    setFocus(); // Otorgar el foco al jugador para recibir eventos de teclado
}

int Jugador::getX() const {
    return x;
}

int Jugador::getY() const {
    return y;
}

void Jugador::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
        speed_y = -5;
        break;
    case Qt::Key_A:
        speed_x = -5;
        break;
    case Qt::Key_S:
        speed_y = 5;
        break;
    case Qt::Key_D:
        speed_x = 5;
        break;
    case Qt::Key_Space:
        emit colocarBomba();  // Emitir señal para colocar la bomba
        break;
    default:
        break;
    }
}

void Jugador::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_S:
        speed_y = 0;
        break;
    case Qt::Key_A:
    case Qt::Key_D:
        speed_x = 0;
        break;
    default:
        break;
    }
}

void Jugador::update() {
    mover(speed_x, speed_y);
}

void Jugador::mover(int dx, int dy) {
    // Actualiza la posición del jugador
    x += dx;
    y += dy;

    QPointF nuevaPos = this->pos() + QPointF(dx, dy);

    // Verificar colisiones en la nueva posición
    this->setPos(nuevaPos);
    for (QGraphicsItem* item : scene()->collidingItems(this)) {
        if (item != this) {
            // Si hay una colisión, revertir el movimiento
            this->setPos(this->pos() - QPointF(dx, dy));
            return;
        }
    }
}
