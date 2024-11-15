#ifndef PUERTA_H
#define PUERTA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>

class Puerta : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Puerta(const QPixmap& pixmap);

private:
    QGraphicsScene* sceneActual;
    Puerta* puerta;

signals:
    void jugadorGanado();  // Señal para indicar que el jugador ha ganado
};

#endif // PUERTA_H
