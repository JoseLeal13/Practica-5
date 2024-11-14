#ifndef PUERTA_H
#define PUERTA_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Puerta : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Puerta(const QPixmap& pixmap);

signals:
    void jugadorGanado();  // Señal para indicar que el jugador ha ganado
};

#endif // PUERTA_H
