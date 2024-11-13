#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPixmap>
#include <QTimer>

class Jugador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Jugador(int startX, int startY, QGraphicsPixmapItem *parent = nullptr);
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
    int frame; // Variable para el control de la animación (frames de la imagen)
    enum class Direction { Right, Left, Down, Up } direction; // Enumeración para las direcciones
    QPixmap frames[6]; // Arreglo para almacenar los 6 cuadros de la animación
    bool animacionActiva;

    void mover(int dx, int dy);
    bool verificarColisionConExplosion(); // Método para verificar colisión con explosión
    void actualizarAnimacion(); // Actualizar el cuadro de la animación

signals:
    void colocarBomba();

public slots:
    void update();
    void perderVida(); // Slot para reducir vidas
};


#endif // JUGADOR_H
