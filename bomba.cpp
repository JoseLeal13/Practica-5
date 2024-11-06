#include "bomba.h"
#include <QGraphicsScene>

Bomba::Bomba(int x, int y, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), timer(new QTimer(this))
{
    QPixmap bombaPixmap("C:\\Users\\Lenovo\\Pictures\\bomba normal.jpg");
    setPixmap(bombaPixmap.scaled(45, 45));
    setPos(x, y);

    connect(timer, &QTimer::timeout, this, &Bomba::explotar);
    timer->start(5000); // La bomba explota después de 5 segundos
}

Bomba::~Bomba() {
    delete timer;  // Eliminar el temporizador al destruir la bomba
}

void Bomba::explotar() {
    QPixmap explosionPixmap("C:\\Users\\Lenovo\\Pictures\\bomba explosion.png");
    explosionPixmap = explosionPixmap.scaled(45, 45);

    // Posiciones de la explosión en las casillas adyacentes (50x50 píxeles)
    QList<QPointF> posicionesExplotar = {
        QPointF(pos().x() - 50, pos().y()),     // Izquierda
        QPointF(pos().x() + 50, pos().y()),     // Derecha
        QPointF(pos().x(), pos().y() - 50),     // Arriba
        QPointF(pos().x(), pos().y() + 50)      // Abajo
    };

    // Añadir las explosiones adyacentes a la escena
    QList<QGraphicsPixmapItem*> explosiones;
    for (const QPointF& posExplosion : posicionesExplotar) {
        QGraphicsPixmapItem* explosion = new QGraphicsPixmapItem(explosionPixmap);
        explosion->setPos(posExplosion);
        scene()->addItem(explosion);
        explosiones.append(explosion);
    }
    setPixmap(explosionPixmap);
    qDebug() << "Bomba central explotada en:" << pos();

    // Sincronizamos la eliminación de la bomba central y las explosiones
    QTimer::singleShot(500, this, [this, explosiones]() {
        // Eliminar la bomba central
        if (scene()) {
            scene()->removeItem(this);  // Remover la bomba central de la escena
        }
        delete this;  // Eliminar la bomba

        // Eliminar las explosiones adyacentes
        for (QGraphicsPixmapItem* explosion : explosiones) {
            if (explosion->scene()) {
                explosion->scene()->removeItem(explosion);  // Remover la explosión de la escena
            }
            delete explosion;  // Eliminar el objeto explosión
        }
    });
}
