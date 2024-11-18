
#include "bomba.h"
#include <QGraphicsScene>

Bomba::Bomba(int x, int y, mapa* mapaRef, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), timer(new QTimer(this)), mapaRef(mapaRef)
{
    QPixmap bombaPixmap("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\bomba normal.jpg");
    setPixmap(bombaPixmap.scaled(45, 45));
    setPos(x, y);

    connect(timer, &QTimer::timeout, this, &Bomba::explotar);
    timer->start(5000); // La bomba explota después de 5 segundos
}

Bomba::~Bomba() {
    delete timer;  // Eliminar el temporizador al destruir la bomba
}

void Bomba::explotar() {
    QPixmap explosionPixmap("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\bomba explosion.png");
    explosionPixmap = explosionPixmap.scaled(45, 45);
    setPixmap(explosionPixmap);

    int fila = pos().y() / 50;
    int columna = pos().x() / 50;

    // Llama a explosionBomba para eliminar los bloques destruibles adyacentes
    mapaRef->explosionBomba(fila, columna, scene());

    // Código para crear y agregar explosiones adyacentes
    QList<QPointF> posicionesExplotar = {
        QPointF(pos().x() - 50, pos().y()),     // Izquierda
        QPointF(pos().x() + 50, pos().y()),     // Derecha
        QPointF(pos().x(), pos().y() - 50),     // Arriba
        QPointF(pos().x(), pos().y() + 50)      // Abajo
    };

    QList<Explosion*> explosiones;
    for (const QPointF& posExplosion : posicionesExplotar) {
        Explosion* explosion = new Explosion(posExplosion);
        scene()->addItem(explosion);
        explosiones.append(explosion);
    }

    QTimer::singleShot(500, this, [this, explosiones]() {
        if (scene()) {
            scene()->removeItem(this);
        }
        delete this;

        for (Explosion* explosion : explosiones) {
            if (explosion->scene()) {
                explosion->scene()->removeItem(explosion);
            }
            delete explosion;
        }
    });

    emit explosionCompleta();
}
