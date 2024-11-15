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
#include "mapa.h"

class Juego : public QGraphicsScene {
    Q_OBJECT

public:
    Juego(QObject* parent = nullptr);

    void pantallaBienvenida();  // Mostrar la pantalla de bienvenida
    void empezarJuego();        // Método para iniciar el juego cuando el botón es presionado
    void iniciarJuego();  // Método para iniciar el juego con la escena
    void setScene(QGraphicsScene* scene);

    void actualizarTiempo();    // Método para actualizar el tiempo
    void CambiarNivel();

    // Getter para el botón empezar (si es necesario)
    QPushButton* getComenzar() const { return comenzar; }

private:
    QGraphicsTextItem* bienvenidaTexto;
    QGraphicsTextItem* puntuacionTexto;
    QGraphicsTextItem* tiempoTexto;
    int puntuacion;
    int tiempo;
    QTimer* tiempo_partida;
    bool juegoIniciado;
    QPushButton* comenzar;    // Botón para iniciar el juego

    QGraphicsScene* sceneActual;  // Escena actual del juego
    mapa* oMapa;                  // Mapa del juego
    QPixmap pixmapPuerta;         // Imagen para la puerta
    QPixmap pixmapSolido;         // Imagen para los elementos sólidos
    QPixmap pixmapDestruible;
};

#endif // JUEGO_H
