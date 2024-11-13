#include "explosion.h"

Explosion::Explosion(QPointF posicion, QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(parent) {
    QPixmap explosionPixmap("C:\\Users\\Lenovo\\Pictures\\bomba explosion.png");
    setPixmap(explosionPixmap.scaled(45, 45));
    setPos(posicion);
}
