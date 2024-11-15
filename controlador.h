#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QApplication>
#include "jugador.h"
#include <QObject>
#include <QGraphicsScene>
#include <QPixmap>
#include "puerta.h"
#include "mapa.h"
#include "juego.h"

class Controlador : public QObject {
    Q_OBJECT

public:
    Controlador();
    void reiniciarJuego();
    void setScene(QGraphicsScene* scene); // Nuevo método
    void detectarColisiones();
    void inicializarPuerta(const QPixmap& pixmapPuerta);


private:
    mapa* oMapa;  // Puntero a mapa
    Jugador* jugador;
    QGraphicsScene* sceneActual;
    QPixmap pixmapSolido;
    QPixmap pixmapDestruible;
    Puerta* puerta;
    Juego* juego;

public slots:
    void mostrarMenuGanaste();
    void mostrarMenuPerdiste();
signals:
    void juegoPerdido();
};

#endif // CONTROLADOR_H
