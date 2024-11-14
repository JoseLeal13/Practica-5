#include "jugador.h"
#include <QKeyEvent>
#include "bomba.h" // Incluir la clase Bomba si es necesaria para verificación

Jugador::Jugador(int startX, int startY, QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent), x(startX), y(startY), speed_x(0), speed_y(0), vidas(3),
    frame(0), direction(Direction::Right), animacionActiva(false) // Inicializamos el frame, la dirección y la animación
{
    setPos(x, y); // Establece la posición inicial
    setFlag(QGraphicsItem::ItemIsFocusable); // Hacer que el objeto sea "focusable"
    setFocus(); // Otorgar el foco al jugador para recibir eventos de teclado

    // Cargar la imagen de la animación (700x622)
    QPixmap playerPixmap("C:/Users/Lenovo/Pictures/Mobile - Amazing Bomberman - Bomberman.png");

    // Dividir la imagen en los cuadros de animación (6 cuadros)
    for (int i = 0; i < 6; ++i) {
        // Extraer cada cuadro de la animación según el índice
        frames[i] = playerPixmap.copy((i % 3) * 700 / 3, (i / 3) * 622 / 2, 700 / 3, 622 / 2);

        // Escalar cada cuadro de la animación a 50x50 manteniendo la relación de aspecto
        frames[i] = frames[i].scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // Inicializar la animación en la dirección 'Right' (derecha)
    setPixmap(frames[0]); // Usamos el primer cuadro de la animación
}

void Jugador::actualizarAnimacion() {
    QPixmap invertedFrame; // Mover la declaración de la variable fuera del switch

    if (speed_x != 0 || speed_y != 0) {
        animacionActiva = true; // La animación está activa mientras se mueve

        // Ciclar entre los frames de la animación (3 cuadros por dirección)
        frame = (frame + 1) % 3; // Cambiar el cuadro de la animación cada vez que se actualiza

        switch (direction) {
        case Direction::Right:
            setPixmap(frames[frame]); // Dirección derecha (fila 1, cuadros 0, 1, 2)
            break;
        case Direction::Left:
            // Dirección izquierda, usamos la fila 1 (derecha) pero invertimos el cuadro
            invertedFrame = frames[frame].transformed(QTransform().scale(-1, 1)); // Invertir la imagen horizontalmente
            setPixmap(invertedFrame);
            break;
        case Direction::Down:
            setPixmap(frames[frame + 3]); // Dirección abajo (fila 2, cuadros 3, 4, 5)
            break;
        case Direction::Up:
            setPixmap(frames[frame + 3]); // Dirección arriba (también usamos la fila 2, cuadros 3, 4, 5, si quieres animación similar)
            break;
        default:
            break;
        }
    } else {
        animacionActiva = false; // La animación se detiene cuando el jugador está quieto

        // Si el jugador está quieto, muestra el primer cuadro según la dirección actual
        switch (direction) {
        case Direction::Right:
            setPixmap(frames[0]); // Cuadro de reposo en dirección derecha
            break;
        case Direction::Left:
            // Cuadro de reposo en dirección izquierda (invertir el cuadro de reposo)
            invertedFrame = frames[0].transformed(QTransform().scale(-1, 1));
            setPixmap(invertedFrame);
            break;
        case Direction::Down:
            setPixmap(frames[3]); // Cuadro de reposo en dirección abajo
            break;
        case Direction::Up:
            setPixmap(frames[3]); // Cuadro de reposo en dirección arriba (similares a abajo)
            break;
        default:
            break;
        }
    }
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
        direction = Direction::Down; // Cambiar la dirección a 'arriba' cuando se presiona W
        break;
    case Qt::Key_A:
        speed_x = -5;
        direction = Direction::Left; // Cambiar la dirección a 'izquierda' cuando se presiona A
        break;
    case Qt::Key_S:
        speed_y = 5;
        direction = Direction::Down; // Cambiar la dirección a 'abajo' cuando se presiona S
        break;
    case Qt::Key_D:
        speed_x = 5;
        direction = Direction::Right; // Cambiar la dirección a 'derecha' cuando se presiona D
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
        actualizarAnimacion(); // Actualiza la animación
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
        qDebug() << "Game Over";
        emit juegoPerdido();
    } else {
        qDebug() << "Vidas restantes:" << vidas;
    }
}
void Jugador::setVidas(int nuevasVidas) {
    vidas = nuevasVidas;  // Establece el nuevo número de vidas
}
