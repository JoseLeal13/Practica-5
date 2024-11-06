#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Jugador(int posicion_x, int posicion_y, QGraphicsPixmapItem *parent = nullptr);
    int getX()const;
    int getY()const;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:

    int x;
    int y;
    int speed_x;
    int speed_y;

    void mover(int dx, int dy);

signals:
    void colocarBomba();

public slots:
    void update();
};

#endif // JUGADOR_H
