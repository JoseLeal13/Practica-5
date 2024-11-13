#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QGraphicsView>
#include <QTimer>
#include "mapa.h"
#include "bomba.h"
#include "jugador.h"

class Juego : public QGraphicsScene {
    Q_OBJECT

public:
    Juego(QObject* parent = nullptr);

    void pantallaBienvenida();  // Mostrar la pantalla de bienvenida
    void iniciarJuego(QGraphicsScene* scene);     // Iniciar el juego

    void actualizarTiempo();    // Método para actualizar el tiempo

private slots:
    void empezarJuego();        // Slot para iniciar el juego cuando el botón es presionado

private:
    QGraphicsTextItem* bienvenidaTexto;
    QGraphicsTextItem* puntuacionTexto;
    QGraphicsTextItem* tiempoTexto;
    int puntuacion;
    int tiempo;
    QTimer* tiempo_partida;
    bool juegoIniciado;
    QPushButton* comenzar;    // Botón para iniciar el juego

};

#endif // JUEGO_H
