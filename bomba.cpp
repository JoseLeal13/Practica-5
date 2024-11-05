#include "bomba.h"
#include <QGraphicsScene>

Bomba::Bomba(int x, int y, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent), timer(new QTimer(this))
{
    QPixmap bombaPixmap("C:\\Users\\Lenovo\\Pictures\\bomba normal.jpg");
    setPixmap(bombaPixmap.scaled(40, 40));
    setPos(x, y);

    connect(timer, &QTimer::timeout, this, &Bomba::explotar);
    timer->start(5000); // La bomba explota después de 5 segundos
}

Bomba::~Bomba() {
    delete timer;
}

void Bomba::explotar() {
    QPixmap explosionPixmap("C:\\Users\\Lenovo\\Pictures\\bomba explosion.png");
    setPixmap(explosionPixmap.scaled(40, 40));

    QTimer::singleShot(500, this, [this]() {
        if (scene()) {
            scene()->removeItem(this); // Remover la bomba de la escena
        }
        delete this; // Eliminar el objeto bomba
    });
}
