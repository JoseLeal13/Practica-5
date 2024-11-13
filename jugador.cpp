#include "jugador.h"
#include <QKeyEvent>
#include "bomba.h" // Incluir la clase Bomba si es necesaria para verificación

Jugador::Jugador(int startX, int startY, QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent), x(startX), y(startY), speed_x(0), speed_y(0), vidas(3)
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

int Jugador::getVidas() const {
    return vidas;
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
        emit colocarBomba();
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
    QPointF nuevaPos = this->pos() + QPointF(dx, dy);
    this->setPos(nuevaPos); // Intentar mover al jugador a la nueva posición

    bool colision = false;
    bool colisionConExplosion = false;

    // Recorre los objetos con los que el jugador colisiona en la nueva posición
    for (QGraphicsItem* item : scene()->collidingItems(this)) {
        // Ignora la bomba misma
        if (dynamic_cast<Bomba*>(item)) {
            continue;
        }

        // Verificar si es una explosión
        Explosion* explosion = dynamic_cast<Explosion*>(item);
        if (explosion) {
            colisionConExplosion = true;
            perderVida(); // El jugador pierde una vida si toca una explosión
            break; // Terminar el bucle al encontrar la primera explosión
        }

        // Si el objeto no es ni una bomba ni una explosión, se trata de un muro u obstáculo
        colision = true;
    }

    if (!colision && !colisionConExplosion) {
        x += dx; // Actualiza la posición X
        y += dy; // Actualiza la posición Y
    } else {
        // Retrocede si hay colisión
        this->setPos(this->pos() - QPointF(dx, dy));
    }
}


bool Jugador::verificarColisionConExplosion() {
    for (QGraphicsItem* item : scene()->collidingItems(this)) {
        if (dynamic_cast<Bomba*>(item)) {
            // Ignorar colisión con bombas
            continue;
        } else if (dynamic_cast<Explosion*>(item)) {
            // Colisionó con una explosión, pierde una vida
            perderVida();
            return true;
        }
    }
    return false;
}

void Jugador::perderVida() {
    vidas--;
    if (vidas <= 0) {
        // Aquí puedes añadir lógica para manejar el "Game Over"
        qDebug() << "Game Over";
    } else {
        qDebug() << "Vidas restantes:" << vidas;
    }
}
