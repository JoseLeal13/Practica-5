#ifndef BOMBA_H
#define BOMBA_H
#include "mapa.h"
#include "explosion.h"
#include <QGraphicsPixmapItem>
#include <QTimer>

class Bomba : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bomba(int x, int y, mapa* mapaRef, QGraphicsItem* parent = nullptr);
    ~Bomba();

public slots:
    void explotar();

private:
    QTimer* timer;
    mapa* mapaRef;

signals:
    void explosionCompleta();
};

#endif // BOMBA_H
