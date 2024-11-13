#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "mapa.h"

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Jugador(int posicion_x, int posicion_y, QGraphicsPixmapItem *parent = nullptr);
    int getX() const;
    int getY() const;
    int getVidas() const; // Método para obtener las vidas restantes
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    int x;
    int y;
    int speed_x;
    int speed_y;
    int vidas; // Variable para contar las vidas del jugador

    void mover(int dx, int dy);
    bool verificarColisionConExplosion(); // Método para verificar colisión con explosión

signals:
    void colocarBomba();

public slots:
    void update();
    void perderVida(); // Slot para reducir vidas
};

extern mapa* mapaRef;

#endif // JUGADOR_H
