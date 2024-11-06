#ifndef BOMBA_H
#define BOMBA_H
#include "mapa.h"

#include <QGraphicsPixmapItem>
#include <QTimer>

class Bomba : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bomba(int x, int y, QGraphicsItem* parent = nullptr);
    ~Bomba();

public slots:
    void explotar();

private:
    QTimer* timer;
};

#endif // BOMBA_H
