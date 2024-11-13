#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Explosion : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Explosion(QPointF posicion, QGraphicsItem* parent = nullptr);
};

#endif // EXPLOSION_H
