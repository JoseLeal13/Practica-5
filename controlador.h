// controlador.h
#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "mapa.h"
#include "jugador.h"
#include <QObject>
#include <QGraphicsScene>
#include <QPixmap>
#include "puerta.h"

class Controlador : public QObject {
    Q_OBJECT

public:
    Controlador();
    void mostrarMenuPerdiste();
    void reiniciarJuego();
    void setScene(QGraphicsScene* scene); // Nuevo método
    void detectarColisiones();
    void mostrarMenuGanaste();

private:
    mapa* oMapa;
    Jugador* jugador; // Agrega el puntero a jugador como miembro de la clase
    QGraphicsScene* sceneActual;
    QPixmap pixmapSolido;
    QPixmap pixmapDestruible;
    Puerta* puerta;

    void CambiarNivel();
    void dibujar(QGraphicsScene* scene, const QPixmap& solido, const QPixmap& destruible);
};

#endif // CONTROLADOR_H
